#include "stdafx.h"

CClient::CClient(SOCKET sockClient) : m_sockClient(sockClient), m_bBreak(TRUE), m_hTread(NULL)
{
	;
}

CClient::~CClient()
{
	closesocket(m_sockClient);
}

//��ʼ�߳�
BOOL CClient::Start()
{
	if (m_hTread == NULL)     //δ�������߳�
	{
		m_hTread = CreateThread(0, 0, ThreadFun, this, 0, 0);
		if (m_hTread == NULL) //�����߳�ʧ��
		{
			return FALSE;
		}

		return TRUE;
	}

	return FALSE;
}

//ֹͣ�߳�
BOOL CClient::Stop()
{
	if (m_hTread != NULL)
	{
		m_bBreak = FALSE;

		WaitForSingleObject(m_hTread, INFINITE);
		CloseHandle(m_hTread);
		m_hTread = NULL;

		return TRUE;
	}

	return FALSE;
}

unsigned int CClient::Run()
{
	char pBuffer[BUF_SIZE] = { 0 };		  //������

	int nStatus = RECV_HEAD;			  //״̬λ��0��ʾ����head��1��ʾ����body
	int nRecvMsgLen = sizeof(TMsgHead);   //���ܵĳ���
	int nRecvTotal = 0;					  //�ܹ����ܳ���
	int nLen = 0;						  //ÿ�ν��ܵĳ���

	char pHead[sizeof(TMsgHead)] = { 0 }; //����ͷ�洢λ��
	char *pUerInformation = NULL;         //�û���Ϣ�洢λ��

	TMsgHead *pMsgHead = (TMsgHead *)pHead; //����ת��

	//��ͻ��˽���ͨ��
	while (m_bBreak)
	{
		nLen = recv(m_sockClient, pBuffer + nRecvTotal, nRecvMsgLen - nRecvTotal, 0);
		if (nLen == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)       //�������ݴ���,�Է������ж�
		{
			printf("recv Msg failed: %d\n", WSAGetLastError());
			return 1;
		}
		else if (nLen == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK) //��ʱδ�յ����ݣ��ȴ�����
		{
			Sleep(100);
			continue;
		}
		else if (nLen == 0)													 //�ͻ����Ѿ��ر�����
		{
			printf("Client has shutdown: %d\n", WSAGetLastError());
			return 1;
		}
		else
		{
			;
		}

		//���ܵ��ܳ���
		nRecvTotal += nLen;

		if (nRecvTotal == nRecvMsgLen)
		{
			//���ݵ�ǰ״̬��ȡָ����Ϣ
			switch (nStatus)
			{
			case RECV_HEAD:
				//��ȡͷ
				memcpy(pHead, pBuffer, nRecvTotal);
				pMsgHead->nLen = htonl(pMsgHead->nLen);

				//����״̬
				memset(pBuffer, 0, BUF_SIZE);
				nStatus = RECV_BODY;
				nRecvTotal = 0;
				nRecvMsgLen = pMsgHead->nLen;
				break;
			case RECV_BODY:
				//����ͷ���
				if (pMsgHead->cHead == HEAD_COMMAND)
				{
					pUerInformation = (char*)realloc(pUerInformation, nRecvMsgLen * sizeof(char));
					memset(pUerInformation, 0, nRecvMsgLen);			  //��ʼ���ռ�
					memcpy(pUerInformation, pBuffer, nRecvTotal);

					TUserInfo *pUser = (TUserInfo *)pUerInformation;
					pUser->nPort = htons(pUser->nPort);

					PrintUser(pUser);

					//������Ϣ
					memset(pHead, 0, sizeof(TMsgHead));
					memset(pBuffer, 0, BUF_SIZE);
					nStatus = RECV_HEAD;
					nRecvTotal = 0;
					nRecvMsgLen = sizeof(TMsgHead);
				}
				break;
			default:
				break;
			}
		}
	}

	if (pUerInformation != NULL)
	{
		delete[]pUerInformation;
	}

	return 0;
}

HANDLE& CClient::GetHandle()
{
	return m_hTread;
}

DWORD WINAPI ThreadFun(LPVOID lpThreadParameter)
{
	CClient *pThread = (CClient *)lpThreadParameter;
	if (pThread != NULL)
	{
		if (pThread->Run() == 1)
		{
			//���н��������Լ�����Դ
			RemoveList(pThread);
		}
		return 0;
	}

	return 0;
}
