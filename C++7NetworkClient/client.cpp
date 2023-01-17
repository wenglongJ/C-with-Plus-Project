#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <WinSock2.h>
#include <windows.h>
#include "TuserInfo.h"
#include <signal.h>

using namespace std;

#pragma warning (disable:4996) 
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll

//宏定义声明
#define BUF_SIZE sizeof(TUserInfo)+sizeof(TMsgHead) //定义缓冲区长度,一个包大小
#define HEAD_COMMAND 0x01		                    //信息头定义宏


//变量声明
char g_cExit = ' ';
bool g_bBreak = TRUE;


//线程函数，发送拼接过信息头的数据
DWORD WINAPI ThreadFun(LPVOID lpThreadParameter);


int csdafas()
{
	//初始化DLL
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 0;
	}

	//定义结构体
	TUserInfo userInformation1;
	memset(&userInformation1, 0, sizeof(TUserInfo));
	strcpy_s(userInformation1.pszAddressIp, "127.0.0.1");
	strcpy_s(userInformation1.pszUser, "线程1");
	strcpy_s(userInformation1.pszPassword, "Software");
	userInformation1.nPort = 4477;

	//定义结构体
	TUserInfo userInformation2;
	memset(&userInformation2, 0, sizeof(TUserInfo));
	strcpy_s(userInformation2.pszAddressIp, "127.0.0.1");
	strcpy_s(userInformation2.pszUser, "线程2");
	strcpy_s(userInformation2.pszPassword, "Software");
	userInformation2.nPort = 4477;

	//线程1
	HANDLE hThread1 = CreateThread(NULL, 0, ThreadFun, &userInformation1, 0, NULL);

	//线程2
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadFun, &userInformation2, 0, NULL);

	printf("请输入q断开与服务器连接：\n\n");
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
	CloseHandle(hThread1); //关闭对线程1的引用

	WaitForSingleObject(hThread2, INFINITE);
	CloseHandle(hThread2); //关闭对线程2的引用

	WSACleanup();
	getchar();
	return 0;
}

DWORD WINAPI ThreadFun(LPVOID lpThreadParameter)
{
	TUserInfo userInformation = *(TUserInfo*)lpThreadParameter;

	//初始化信息头
	TMsgHead msgHead;
	msgHead.cHead = HEAD_COMMAND;
	msgHead.nLen = sizeof(userInformation);

	//向服务器发起请求的结构体
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));    //每个字节都用0填充
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(userInformation.pszAddressIp);
	sockAddr.sin_port = htons(userInformation.nPort);

	//如果本机为大端则转化为小端，为小端则不做处理，转化成符合网络协议的数据
	userInformation.nPort = ntohs(userInformation.nPort);
	msgHead.nLen = ntohl(msgHead.nLen);

	//建立缓冲区
	char pBuffer[BUF_SIZE] = { 0 };

	//将信息头与用户信息拼接
	memcpy(pBuffer, &msgHead, sizeof(TMsgHead));
	memcpy(pBuffer + sizeof(TMsgHead), &userInformation, sizeof(TUserInfo));

	//创建套接字
	SOCKET sockSend = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockSend == SOCKET_ERROR)
	{
		printf("socket failed: %d\n", WSAGetLastError());
		closesocket(sockSend);
		return 0;
	}

	//设置成非阻塞模式。
	const unsigned long g_ulNonblockSock = 1;

	int nSocketNonBlockSend = ioctlsocket(sockSend, FIONBIO, (unsigned long *)&g_ulNonblockSock);
	if (nSocketNonBlockSend == SOCKET_ERROR) //设置失败。
	{
		printf("ioctlsocket failed: %d\n", WSAGetLastError());
		closesocket(sockSend);
		return 0;
	}

	//连接服务器
	if (connect(sockSend, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		//当connect正在连接
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			printf("connect failed: %d\n", WSAGetLastError());
			closesocket(sockSend);
			return 0;
		}
	}

	//select等待connect成功
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

	printf("%s  与服务器建立连接!\n", userInformation.pszUser);

	while (g_bBreak)
	{
		//发送数据
		int nIdx = 0;
		int nSendlen = BUF_SIZE;

		//发送数据，防止一次未发送完
		while (nSendlen > 0)
		{
			int nSendMsglen = send(sockSend, pBuffer + nIdx, nSendlen, 0);
			//发送失败
			if (nSendMsglen == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
			{
				printf("send failed: %d\n", WSAGetLastError());
				closesocket(sockSend);			//关闭套接字
				return 0;
			}
			else if (nSendMsglen == SOCKET_ERROR && WSAGetLastError() == WSAEWOULDBLOCK) //无空间，等待
			{
				Sleep(100);
				continue;
			}
			else   //0或者正数视为发送成功
			{
				;
			}

			nSendlen -= nSendMsglen;
			nIdx += nSendMsglen;
		}

		printf("%s  发送一个包!\n", userInformation.pszUser);

		Sleep(10000);
	}

	//关闭套接字
	closesocket(sockSend);
	return 0;
}
