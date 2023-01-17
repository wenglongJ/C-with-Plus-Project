
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

const int MAX_BUF_LEN = 255;
typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;

typedef struct package {
	u8_t version;
	u8_t code;
	u16_t xid;
	u16_t httpport;
	u16_t videoport;
	u32_t ydhcp;
	u8_t yipaddr[4];
	u8_t ymask[4];
	u8_t ygateway[4];
	u8_t ydns[4];
	u8_t cmac[8];
	u16_t optlen;
	u8_t options[1];
} IPCamPackage;

#define PKG_SIZE                400
#define IPCAM_CODE_SEARCHALL    4

int main()
{
	WORD wVersionRequested;
	WSADATA wasData;//指向WinSocket信息结构的指针
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	// 初始化winsock库，使用socket的前提
	err = WSAStartup(wVersionRequested, &wasData);
	if (err != 0)
	{
		return -1;
	}
	if (LOBYTE(wasData.wVersion) != 2 || HIBYTE(wasData.wVersion) != 2)
	{
		WSACleanup();
		return -1;
	}
	SOCKET conn_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (conn_sock == INVALID_SOCKET)
	{
		err = WSAGetLastError();
		printf("socket error:%d\n", err);
		closesocket(conn_sock);
		WSACleanup();
		return -1;
	}
	bool bOpt = true;
	//打开广播选项
	setsockopt(conn_sock, SOL_SOCKET, SO_BROADCAST , (char*)&bOpt, sizeof(bOpt));

	char sendBuf[PKG_SIZE] = { 0x00 };
	IPCamPackage *pkg, *PkgRecv;
	pkg = (IPCamPackage *)sendBuf;
	// 交互参数设置
	pkg->code = IPCAM_CODE_SEARCHALL;
	pkg->xid = 0xFFFF;

	// 设置发往的地址
	SOCKADDR_IN saUdpServ;
	memset(&saUdpServ, 0, sizeof(saUdpServ));
	saUdpServ.sin_family = AF_INET;
	saUdpServ.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);
	saUdpServ.sin_port = htons(60021);
	int nSize = sizeof(SOCKADDR_IN);

	//memset(buff, 0, MAX_BUF_LEN);
	int nLoop = 0;
	char* ip = NULL;
	while (1) {
		nLoop++;
		//sprintf_s(sendBuf, "Message %d", nLoop);
		int nSendSize = sendto(conn_sock, sendBuf, sizeof(IPCamPackage), 0, (SOCKADDR*)&saUdpServ, nSize);
		if (nSendSize == SOCKET_ERROR)
		{
			err = WSAGetLastError();
			printf("sendto error:%d\n", err);
			closesocket(conn_sock);
			WSACleanup();
			return -1;
		}
		//printf("send: %s\n", sizeof(sendBuf));
		Sleep(5000);
	}

	closesocket(conn_sock);
	WSACleanup();
	return 0;
}