#include <stdio.h>
#include <winsock2.h>
#include<iostream>
using namespace std;
#pragma warning(disable : 4996)
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
int main() {
	//初始化 DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//创建套接字
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//绑定套接字
	struct sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;  //使用IPv4地址
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
	sockAddr.sin_port = htons(3306);  //端口
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//进入监听状态
	listen(servSock, 20);
	//接收客户端请求
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	//输出客户端套接字
	sockaddr_in clntAddr_in;
	memcpy(&clntAddr_in, &clntAddr, sizeof(clntAddr_in));
	// 取得ip和端口号
	char port[50] = "";
	sprintf(port, inet_ntoa(clntAddr_in.sin_addr));
	cout << ntohs(clntAddr_in.sin_port) << endl;
	//向客户端发送数据
	char *str = "Hello World!";
	send(clntSock, str, strlen(str) + sizeof(char), NULL);
	send(clntSock, str, strlen(str) + sizeof(char), NULL);

	//关闭套接字
	closesocket(clntSock);
	closesocket(servSock);
	//终止 DLL 的使用
	WSACleanup();
	return 0;
}