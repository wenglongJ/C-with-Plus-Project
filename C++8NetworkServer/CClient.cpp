#include "stdafx.h"

CClient::CClient(SOCKET sockClient) : m_sockClient(sockClient), m_bBreak(TRUE), m_hTread(NULL)
{
	;
}

CClient::~CClient()
{
	closesocket(m_sockClient);
}

//开始线程
BOOL CClient::Start()
{
	if (m_hTread == NULL)     //未创建的线程
	{
		m_hTread = CreateThread(0, 0, ThreadFun, this, 0, 0);
		if (m_hTread == NULL) //创建线程失败
		{
			return FALSE;
		}

		return TRUE;
	}

	return FALSE;
}

//停止线程
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
	char pBuffer[BUF_SIZE] = { 0 };		  //缓冲区

	int nStatus = RECV_HEAD;			  //状态位，0表示接受head，1表示接受body
	int nRecvMsgLen = sizeof(TMsgHead);   //接受的长度
	int nRecvTotal = 0;					  //总共接受长度
	int nLen = 0;						  //每次接受的长度

	char pHead[sizeof(TMsgHead)] = { 0 }; //数据头存储位置
	char *pUerInformation = NULL;         //用户信息存储位置

	TMsgHead *pMsgHead = (TMsgHead *)pHead; //进行转换

	//与客户端进行通信
	while (m_bBreak)
	{
		nLen = recv(m_sockClient, pBuffer + nRecvTotal, nRecvMsgLen - nRecvTotal, 0);
		if (nLen == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)       //接受数据错误,对方可能中断
		{
			printf("recv Msg failed: %d\n", WSAGetLastError());
			return 1;
		}
		else if (nLen == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK) //暂时未收到数据，等待数据
		{
			Sleep(100);
			continue;
		}
		else if (nLen == 0)													 //客户端已经关闭连接
		{
			printf("Client has shutdown: %d\n", WSAGetLastError());
			return 1;
		}
		else
		{
			;
		}

		//接受到总长度
		nRecvTotal += nLen;

		if (nRecvTotal == nRecvMsgLen)
		{
			//根据当前状态获取指定信息
			switch (nStatus)
			{
			case RECV_HEAD:
				//获取头
				memcpy(pHead, pBuffer, nRecvTotal);
				pMsgHead->nLen = htonl(pMsgHead->nLen);

				//重置状态
				memset(pBuffer, 0, BUF_SIZE);
				nStatus = RECV_BODY;
				nRecvTotal = 0;
				nRecvMsgLen = pMsgHead->nLen;
				break;
			case RECV_BODY:
				//根据头拆包
				if (pMsgHead->cHead == HEAD_COMMAND)
				{
					pUerInformation = (char*)realloc(pUerInformation, nRecvMsgLen * sizeof(char));
					memset(pUerInformation, 0, nRecvMsgLen);			  //初始化空间
					memcpy(pUerInformation, pBuffer, nRecvTotal);

					TUserInfo *pUser = (TUserInfo *)pUerInformation;
					pUser->nPort = htons(pUser->nPort);

					PrintUser(pUser);

					//重置信息
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
			//运行结束清理自己的资源
			RemoveList(pThread);
		}
		return 0;
	}

	return 0;
}
