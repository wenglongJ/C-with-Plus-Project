#include <stdio.h>
#include <winsock2.h>
#include<iostream>
using namespace std;
#pragma warning(disable : 4996)
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll
int main() {
	//��ʼ�� DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//�����׽���
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//���׽���
	struct sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ
	sockAddr.sin_port = htons(3306);  //�˿�
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//�������״̬
	listen(servSock, 20);
	//���տͻ�������
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	//����ͻ����׽���
	sockaddr_in clntAddr_in;
	memcpy(&clntAddr_in, &clntAddr, sizeof(clntAddr_in));
	// ȡ��ip�Ͷ˿ں�
	char port[50] = "";
	sprintf(port, inet_ntoa(clntAddr_in.sin_addr));
	cout << ntohs(clntAddr_in.sin_port) << endl;
	//��ͻ��˷�������
	char *str = "Hello World!";
	send(clntSock, str, strlen(str) + sizeof(char), NULL);
	send(clntSock, str, strlen(str) + sizeof(char), NULL);

	//�ر��׽���
	closesocket(clntSock);
	closesocket(servSock);
	//��ֹ DLL ��ʹ��
	WSACleanup();
	return 0;
}