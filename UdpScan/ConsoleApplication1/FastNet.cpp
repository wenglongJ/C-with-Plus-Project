#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"
#include <string.h>
#include <sys/types.h>
#include <WinSock2.h>
#include <windows.h>
#include <errno.h>

#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

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

 char sendBuf[PKG_SIZE] = { 0x00 };
char inBuf[PKG_SIZE] = { 0x00 };

int InitRoute(int flag);

int main(void)
{
    // 添加全网段路由网关
    InitRoute(1);

    IPCamPackage *pkg, *PkgRecv;
    pkg = (IPCamPackage *) sendBuf;
    // 交互参数设置
    pkg->code = IPCAM_CODE_SEARCHALL;
    pkg->xid = 0xFFFF;

    int brdcFd, sendBytes, recvBytes;
    int optval = 1;
    struct sockaddr_in theirAddr;
    int sockAddrSize = sizeof(struct sockaddr_in);

    if ((brdcFd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
        printf("Socket fail !\n");
        return -1;
    }
    // 设置超时时间
    struct timeval tv;
    tv.tv_sec = 1;
    tv.tv_usec = 0;
    //if (setsockopt(brdcFd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
    //    printf("Socket option SO_RCVTIMEO not support\n");
    //    return -1;
    //}

    //setsockopt(brdcFd, SOL_SOCKET, SO_BROADCAST | SO_REUSEADDR, &optval, sizeof(int));
    memset(&theirAddr, 0,sizeof(struct sockaddr_in));
    theirAddr.sin_family = AF_INET;
    theirAddr.sin_addr.s_addr = inet_addr("255.255.255.255");
    theirAddr.sin_port = htons(60021);

    if ((sendBytes = sendto(brdcFd, sendBuf, sizeof(IPCamPackage), 0, (struct sockaddr *)&theirAddr, sockAddrSize)) == -1) {
        printf("Sendto fail, Error Code: %d\n", errno);
        return -1;
    }

    printf("[MAC]                [IP]               [MASK]             [GATEWAY]          [DNS]\n");
    while (1) {
        if ((recvBytes = recvfrom(brdcFd, inBuf, PKG_SIZE, 0, (struct sockaddr *)&theirAddr, &sockAddrSize)) == -1) {
            break;
        }
        PkgRecv = (IPCamPackage *) & inBuf;
        printf("%02X:%02X:%02X:%02X:%02X:%02X    ", PkgRecv->cmac[0], PkgRecv->cmac[1], PkgRecv->cmac[2], PkgRecv->cmac[3], PkgRecv->cmac[4], PkgRecv->cmac[5]);
        printf("%-3d.%-3d.%-3d.%-3d    ", PkgRecv->yipaddr[0], PkgRecv->yipaddr[1], PkgRecv->yipaddr[2], PkgRecv->yipaddr[3]);
        printf("%-3d.%-3d.%-3d.%-3d    ", PkgRecv->ymask[0], PkgRecv->ymask[1], PkgRecv->ymask[2], PkgRecv->ymask[3]);
        printf("%-3d.%-3d.%-3d.%-3d    ", PkgRecv->ygateway[0], PkgRecv->ygateway[1], PkgRecv->ygateway[2], PkgRecv->ygateway[3]);
        printf("%-3d.%-3d.%-3d.%-3d\n", PkgRecv->ydns[0], PkgRecv->ydns[1], PkgRecv->ydns[2], PkgRecv->ydns[3]);
    }
    closesocket(brdcFd);
    InitRoute(0);
    return 0;
}

int InitRoute(int flag)
{
    if (flag) {
        system("sudo route add -net 0.0.0.0 dev eth0 > /dev/null 2>&1");
    } else {
        system("sudo route del -net 0.0.0.0 dev eth0 > /dev/null 2>&1");
    }
    return 0;
}
