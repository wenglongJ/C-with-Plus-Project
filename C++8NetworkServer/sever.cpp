// C++��ϰ8network�����.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#pragma warning (disable:4996)
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll

//��������
HANDLE g_hMutexPrint = NULL;					 //������
HANDLE g_hMutexList = NULL;                      //��������б�
bool g_bBreak = TRUE;						     //ctrl+c����ѭ���������˳�
std::list<CClient *> g_lstCClient;				 //�������е��߳��б�

int sss()
{
	//��ʼ��DDL
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 0;
	}
	
	if (!TestSever())
	{
		cout << "����������ʧ��" << endl;
	}
	else
	{
		;
	}

	WSACleanup();

	getchar();
	return 0;
}

BOOL TestSever()
{
	//����һ��������
	g_hMutexPrint = CreateMutex(NULL, FALSE, NULL);
	g_hMutexList = CreateMutex(NULL, FALSE, NULL);

	//�����׽���
	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, 0);
	if (sockServer == SOCKET_ERROR)
	{
		cout << "socket failed:" << WSAGetLastError() << endl;
		closesocket(sockServer);
		return FALSE;
	}

	//���óɷ�����ģʽ��
	const unsigned long g_ulNonblockSock = 1;		 //������

	int nSocketNonBlockSend = ioctlsocket(sockServer, FIONBIO, (unsigned long *)&g_ulNonblockSock);
	if (nSocketNonBlockSend == SOCKET_ERROR) //����ʧ�ܡ�
	{
		cout << "ioctlsocket failed:" << WSAGetLastError() << endl;
		closesocket(sockServer);
		return FALSE;
	}

	//�������Ľṹ��
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));				//ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;						//ʹ��IPv4��ַ
	sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);		//�����IP��ַ
	sockAddr.sin_port = htons(4477);					//�˿�

	//���׽���
	if (bind(sockServer, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		cout << "bind failed:" << WSAGetLastError() << endl;
		closesocket(sockServer);
		return FALSE;
	}

	//�������״̬,�������ͬʱ����10��
	if (listen(sockServer, 10) == SOCKET_ERROR)
	{
		cout << "listen failed:" << WSAGetLastError() << endl;
		closesocket(sockServer);
		return FALSE;
	}

	//���տͻ�������
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);

	//����ctrl+c�˳��ź�
	signal(SIGINT, Signal_Handler);

	while (g_bBreak)
	{
		SOCKET sockClient = accept(sockServer, (SOCKADDR*)&clntAddr, &nSize);

		//���յ��ͻ�������
		if (sockClient != INVALID_SOCKET)
		{
			//�ж��׽����Ƿ�ɶ������ɶ��������׽���,���׽�����Ч
			fd_set fd_read;
			FD_ZERO(&fd_read);
			FD_SET(sockClient, &fd_read);
			timeval timeout = { 1,0 };

			int nRet = select(0, &fd_read, NULL, NULL, &timeout);
			if (nRet == SOCKET_ERROR || !FD_ISSET(sockClient, &fd_read))
			{
				cout << "select failed:" << WSAGetLastError() << endl;
				closesocket(sockClient);
				continue;
			}

			//�����ӳ������������ޣ�������������
			if (g_lstCClient.size() >= MAX_CLIENT_NUMS)
			{
				printf("���������������������ֹͣ��\n");
				closesocket(sockClient);
				continue;
			}
			else //С�������������������һ���߳���
			{
				CClient *pThread = new CClient(sockClient);

				//�����̣߳������ɹ������б�ʧ��ɾ����Դ
				if (pThread->Start())
				{
					AddList(pThread);
				}
				else
				{
					cout << "CClient Start fail!" << endl;
					delete pThread;
				}
			}
		}
	}

	//�رշ������׽��֣�����������
	closesocket(sockServer);

	//��ͷ�ر������߳�,�ٹرշ�����
	for (auto itrClient = g_lstCClient.begin(); itrClient != g_lstCClient.end(); itrClient++)
	{
		(*itrClient)->Stop();
		//�ͷ���Դ
		delete *itrClient;
	}

	cout << "�������ѹرգ�" << endl;

	return TRUE;
}

void PrintUser(const TUserInfo *pUserInformation)
{
	if (pUserInformation == NULL)
	{
		return;
	}

	//��ӡ�û���Ϣ,ͨ���ź�����ֹ��ӡ˳�����
	WaitForSingleObject(g_hMutexPrint, INFINITE);

	cout << "�û�����" << pUserInformation->pszUser << endl;
	cout << "���룺" << pUserInformation->pszPassword << endl;
	cout << "��ַ��" << pUserInformation->pszAddressIp << endl;
	cout << "�˿ںţ�" << pUserInformation->nPort << endl;
	cout << endl;

	ReleaseMutex(g_hMutexPrint);
}

void Signal_Handler(int nSig)
{
	if (nSig == SIGINT)
	{
		// ctrl+c�˳�ʱִ�еĴ���
		g_bBreak = false;
	}
}

void AddList(CClient *pCClient)
{
	if (pCClient != NULL)
	{
		if (pCClient->GetHandle() != NULL)
		{
			WaitForSingleObject(g_hMutexList, INFINITE);
			g_lstCClient.push_back(pCClient);
			ReleaseMutex(g_hMutexList);
		}
	}
}

void RemoveList(CClient *pCClient)
{
	if (pCClient != NULL)
	{
		//�߳�������ֹͣ
		if (pCClient->GetHandle() != NULL)
		{
			CloseHandle(pCClient->GetHandle());
			pCClient->GetHandle() = NULL;
		}

		WaitForSingleObject(g_hMutexList, INFINITE);
		g_lstCClient.remove(pCClient);
		ReleaseMutex(g_hMutexList);

		//�����Լ�����Դ
		delete pCClient;
	}
}
