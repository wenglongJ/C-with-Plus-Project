#include <stdio.h>
#include <windows.h>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll
#define BUF_SIZE 100
int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//�����׽���
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);
	//���׽���
	struct sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ
	sockAddr.sin_port = htons(1234);  //�˿�
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//�������״̬
	listen(servSock, 20);
	//���տͻ�������
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	char buffer[BUF_SIZE] = { 0 };  //������
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	Sleep(10000);  //ע������ó�����ͣ10��
				   //���տͻ��˷��������ݣ���ԭ������
	int recvLen = recv(clntSock, buffer, BUF_SIZE, 0);
	send(clntSock, buffer, recvLen, 0);
	//�ر��׽��ֲ���ֹDLL��ʹ��
	closesocket(clntSock);
	closesocket(servSock);
	WSACleanup();
	return 0;
}