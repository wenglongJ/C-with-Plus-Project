#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <WinSock2.h>
#include <windows.h>
#include "TuserInfo.h"
#include <signal.h>

using namespace std;

#pragma warning (disable:4996) 
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll

//�궨������
#define BUF_SIZE sizeof(TUserInfo)+sizeof(TMsgHead) //���建��������,һ������С
#define HEAD_COMMAND 0x01		                    //��Ϣͷ�����


//��������
char g_cExit = ' ';
bool g_bBreak = TRUE;


//�̺߳���������ƴ�ӹ���Ϣͷ������
DWORD WINAPI ThreadFun(LPVOID lpThreadParameter);


int csdafas()
{
	//��ʼ��DLL
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 0;
	}

	//����ṹ��
	TUserInfo userInformation1;
	memset(&userInformation1, 0, sizeof(TUserInfo));
	strcpy_s(userInformation1.pszAddressIp, "127.0.0.1");
	strcpy_s(userInformation1.pszUser, "�߳�1");
	strcpy_s(userInformation1.pszPassword, "Software");
	userInformation1.nPort = 4477;

	//����ṹ��
	TUserInfo userInformation2;
	memset(&userInformation2, 0, sizeof(TUserInfo));
	strcpy_s(userInformation2.pszAddressIp, "127.0.0.1");
	strcpy_s(userInformation2.pszUser, "�߳�2");
	strcpy_s(userInformation2.pszPassword, "Software");
	userInformation2.nPort = 4477;

	//�߳�1
	HANDLE hThread1 = CreateThread(NULL, 0, ThreadFun, &userInformation1, 0, NULL);

	//�߳�2
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadFun, &userInformation2, 0, NULL);

	printf("������q�Ͽ�����������ӣ�\n\n");
	cin >> g_cExit;
	switch (g_cExit)
	{
	case 'q':
		g_bBreak = FALSE;
		break;
	default:
		break;
	}

	WaitForSingleObject(hThread1, INFINITE);
	CloseHandle(hThread1); //�رն��߳�1������

	WaitForSingleObject(hThread2, INFINITE);
	CloseHandle(hThread2); //�رն��߳�2������

	WSACleanup();
	getchar();
	return 0;
}

DWORD WINAPI ThreadFun(LPVOID lpThreadParameter)
{
	TUserInfo userInformation = *(TUserInfo*)lpThreadParameter;

	//��ʼ����Ϣͷ
	TMsgHead msgHead;
	msgHead.cHead = HEAD_COMMAND;
	msgHead.nLen = sizeof(userInformation);

	//���������������Ľṹ��
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));    //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(userInformation.pszAddressIp);
	sockAddr.sin_port = htons(userInformation.nPort);

	//�������Ϊ�����ת��ΪС�ˣ�ΪС����������ת���ɷ�������Э�������
	userInformation.nPort = ntohs(userInformation.nPort);
	msgHead.nLen = ntohl(msgHead.nLen);

	//����������
	char pBuffer[BUF_SIZE] = { 0 };

	//����Ϣͷ���û���Ϣƴ��
	memcpy(pBuffer, &msgHead, sizeof(TMsgHead));
	memcpy(pBuffer + sizeof(TMsgHead), &userInformation, sizeof(TUserInfo));

	//�����׽���
	SOCKET sockSend = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockSend == SOCKET_ERROR)
	{
		printf("socket failed: %d\n", WSAGetLastError());
		closesocket(sockSend);
		return 0;
	}

	//���óɷ�����ģʽ��
	const unsigned long g_ulNonblockSock = 1;

	int nSocketNonBlockSend = ioctlsocket(sockSend, FIONBIO, (unsigned long *)&g_ulNonblockSock);
	if (nSocketNonBlockSend == SOCKET_ERROR) //����ʧ�ܡ�
	{
		printf("ioctlsocket failed: %d\n", WSAGetLastError());
		closesocket(sockSend);
		return 0;
	}

	//���ӷ�����
	if (connect(sockSend, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		//��connect��������
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			printf("connect failed: %d\n", WSAGetLastError());
			closesocket(sockSend);
			return 0;
		}
	}

	//select�ȴ�connect�ɹ�
	fd_set fd_write;
	FD_ZERO(&fd_write);
	FD_SET(sockSend, &fd_write);
	timeval timeout = { 1,0 };

	if (select(0, NULL, &fd_write, NULL, &timeout) != 1 || !FD_ISSET(sockSend, &fd_write))
	{
		printf("select failed: %d\n", WSAGetLastError());
		closesocket(sockSend);
		return 0;
	}

	printf("%s  ���������������!\n", userInformation.pszUser);

	while (g_bBreak)
	{
		//��������
		int nIdx = 0;
		int nSendlen = BUF_SIZE;

		//�������ݣ���ֹһ��δ������
		while (nSendlen > 0)
		{
			int nSendMsglen = send(sockSend, pBuffer + nIdx, nSendlen, 0);
			//����ʧ��
			if (nSendMsglen == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
			{
				printf("send failed: %d\n", WSAGetLastError());
				closesocket(sockSend);			//�ر��׽���
				return 0;
			}
			else if (nSendMsglen == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK) //�޿ռ䣬�ȴ�
			{
				Sleep(100);
				continue;
			}
			else   //0����������Ϊ���ͳɹ�
			{
				;
			}

			nSendlen -= nSendMsglen;
			nIdx += nSendMsglen;
		}

		printf("%s  ����һ����!\n", userInformation.pszUser);

		Sleep(10000);
	}

	//�ر��׽���
	closesocket(sockSend);
	return 0;
}
