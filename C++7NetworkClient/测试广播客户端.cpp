
#include "stdafx.h"
#include <iostream>
#include <WinSock2.h>

#pragma  comment(lib, "ws2_32.lib")

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

int ssss()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return -1;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		return -1;
	}
	char inBuf[PKG_SIZE] = {0};

	IPCamPackage *pkg, *PkgRecv;

	SOCKET clientSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (INVALID_SOCKET == clientSock)
	{
		err = WSAGetLastError();
		printf("socket error:%d\n", err);
		WSACleanup();
		return -1;
	}
	//创建本地地址信息并绑定
	SOCKADDR_IN sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(60021);
	if (bind(clientSock, (SOCKADDR*)&sin, sizeof(sin)) != 0)
	{
		err = WSAGetLastError();
		printf("bind error:%d\n", err);
		closesocket(clientSock);
		WSACleanup();
		return -1;
	}

	SOCKADDR_IN clientAddr;
	int addrLen = sizeof(clientAddr);
	int nSize;


	while (1) {
		nSize = recvfrom(clientSock, inBuf, sizeof(IPCamPackage), 0, (SOCKADDR*)&clientAddr, &addrLen);
		if (nSize == SOCKET_ERROR)
		{
			err = WSAGetLastError();
			printf("recv error:%d\n", err);
			break;
		}
		PkgRecv = (IPCamPackage *)& inBuf;
		printf("%02X:%02X:%02X:%02X:%02X:%02X    ", PkgRecv->cmac[0], PkgRecv->cmac[1], PkgRecv->cmac[2], PkgRecv->cmac[3], PkgRecv->cmac[4], PkgRecv->cmac[5]);
		printf("%-3d.%-3d.%-3d.%-3d    ", PkgRecv->yipaddr[0], PkgRecv->yipaddr[1], PkgRecv->yipaddr[2], PkgRecv->yipaddr[3]);
		printf("%-3d.%-3d.%-3d.%-3d    ", PkgRecv->ymask[0], PkgRecv->ymask[1], PkgRecv->ymask[2], PkgRecv->ymask[3]);
		printf("%-3d.%-3d.%-3d.%-3d    ", PkgRecv->ygateway[0], PkgRecv->ygateway[1], PkgRecv->ygateway[2], PkgRecv->ygateway[3]);
		printf("%-3d.%-3d.%-3d.%-3d\n", PkgRecv->ydns[0], PkgRecv->ydns[1], PkgRecv->ydns[2], PkgRecv->ydns[3]);
	}

	closesocket(clientSock);
	WSACleanup();
	return 0;
}