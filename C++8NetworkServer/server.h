#pragma once

//�궨������
#define BUF_SIZE 1000       //��������С
#define HEAD_COMMAND 0x01	//��Ϣͷ�����
#define MAX_CLIENT_NUMS 20  //����ͻ������ӵ������Ŀ
#define RECV_HEAD 0         //����HEAD
#define RECV_BODY 1			//����BODY

//��������
//�̺߳����������ܵ�һ������ʹ���һ���߳�ȥ����
DWORD WINAPI ThreadFun(LPVOID lpThreadParameter);

//���������Ժ���
BOOL TestSever();

//��ӡ����
void PrintUser(const TUserInfo *userInformation);

//crtl+c�˳��źŴ�����
void Signal_Handler(int nSig);

//����̵߳��߳��б���
void AddList(CClient *pCClient);		

//���̴߳��б����Ƴ�,���ͷ���Դ
void RemoveList(CClient *pCClient);	