#include <stdio.h>
#include <windows.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
#define BUF_SIZE 100
int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//创建套接字
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);
	//绑定套接字
	struct sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;  //使用IPv4地址
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
	sockAddr.sin_port = htons(1234);  //端口
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//进入监听状态
	listen(servSock, 20);
	//接收客户端请求
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	char buffer[BUF_SIZE] = { 0 };  //缓冲区
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	Sleep(10000);  //注意这里，让程序暂停10秒
				   //接收客户端发来的数据，并原样返回
	int recvLen = recv(clntSock, buffer, BUF_SIZE, 0);
	send(clntSock, buffer, recvLen, 0);
	//关闭套接字并终止DLL的使用
	closesocket(clntSock);
	closesocket(servSock);
	WSACleanup();
	return 0;
}