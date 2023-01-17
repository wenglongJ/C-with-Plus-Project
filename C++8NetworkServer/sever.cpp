// C++练习8network服务端.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#pragma warning (disable:4996)
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

//变量声明
HANDLE g_hMutexPrint = NULL;					 //互斥量
HANDLE g_hMutexList = NULL;                      //互斥访问列表
bool g_bBreak = TRUE;						     //ctrl+c结束循环，正常退出
std::list<CClient *> g_lstCClient;				 //正在运行的线程列表

int sss()
{
	//初始化DDL
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 0;
	}
	
	if (!TestSever())
	{
		cout << "建立服务器失败" << endl;
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
	//创建一个互斥量
	g_hMutexPrint = CreateMutex(NULL, FALSE, NULL);
	g_hMutexList = CreateMutex(NULL, FALSE, NULL);

	//创建套接字
	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, 0);
	if (sockServer == SOCKET_ERROR)
	{
		cout << "socket failed:" << WSAGetLastError() << endl;
		closesocket(sockServer);
		return FALSE;
	}

	//设置成非阻塞模式。
	const unsigned long g_ulNonblockSock = 1;		 //非阻塞

	int nSocketNonBlockSend = ioctlsocket(sockServer, FIONBIO, (unsigned long *)&g_ulNonblockSock);
	if (nSocketNonBlockSend == SOCKET_ERROR) //设置失败。
	{
		cout << "ioctlsocket failed:" << WSAGetLastError() << endl;
		closesocket(sockServer);
		return FALSE;
	}

	//服务器的结构体
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));				//每个字节都用0填充
	sockAddr.sin_family = PF_INET;						//使用IPv4地址
	sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);		//具体的IP地址
	sockAddr.sin_port = htons(4477);					//端口

	//绑定套接字
	if (bind(sockServer, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		cout << "bind failed:" << WSAGetLastError() << endl;
		closesocket(sockServer);
		return FALSE;
	}

	//进入监听状态,队列最多同时接受10个
	if (listen(sockServer, 10) == SOCKET_ERROR)
	{
		cout << "listen failed:" << WSAGetLastError() << endl;
		closesocket(sockServer);
		return FALSE;
	}

	//接收客户端请求
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);

	//接受ctrl+c退出信号
	signal(SIGINT, Signal_Handler);

	while (g_bBreak)
	{
		SOCKET sockClient = accept(sockServer, (SOCKADDR*)&clntAddr, &nSize);

		//接收到客户端请求
		if (sockClient != INVALID_SOCKET)
		{
			//判断套接字是否可读，不可读跳过此套接字,此套接字无效
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

			//当连接超过服务器上限，结束服务器。
			if (g_lstCClient.size() >= MAX_CLIENT_NUMS)
			{
				printf("超出最大连接数！服务器停止！\n");
				closesocket(sockClient);
				continue;
			}
			else //小于最大连接数量，创建一个线程类
			{
				CClient *pThread = new CClient(sockClient);

				//启动线程，启动成功加入列表，失败删除资源
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

	//关闭服务器套接字，不接受连接
	closesocket(sockServer);

	//从头关闭所有线程,再关闭服务器
	for (auto itrClient = g_lstCClient.begin(); itrClient != g_lstCClient.end(); itrClient++)
	{
		(*itrClient)->Stop();
		//释放资源
		delete *itrClient;
	}

	cout << "服务器已关闭！" << endl;

	return TRUE;
}

void PrintUser(const TUserInfo *pUserInformation)
{
	if (pUserInformation == NULL)
	{
		return;
	}

	//打印用户信息,通过信号量防止打印顺序出错
	WaitForSingleObject(g_hMutexPrint, INFINITE);

	cout << "用户名：" << pUserInformation->pszUser << endl;
	cout << "密码：" << pUserInformation->pszPassword << endl;
	cout << "地址：" << pUserInformation->pszAddressIp << endl;
	cout << "端口号：" << pUserInformation->nPort << endl;
	cout << endl;

	ReleaseMutex(g_hMutexPrint);
}

void Signal_Handler(int nSig)
{
	if (nSig == SIGINT)
	{
		// ctrl+c退出时执行的代码
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
		//线程运行完停止
		if (pCClient->GetHandle() != NULL)
		{
			CloseHandle(pCClient->GetHandle());
			pCClient->GetHandle() = NULL;
		}

		WaitForSingleObject(g_hMutexList, INFINITE);
		g_lstCClient.remove(pCClient);
		ReleaseMutex(g_hMutexList);

		//清理自己的资源
		delete pCClient;
	}
}
