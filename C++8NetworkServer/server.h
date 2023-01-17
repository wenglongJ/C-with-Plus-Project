#pragma once

//宏定义声明
#define BUF_SIZE 1000       //缓冲区大小
#define HEAD_COMMAND 0x01	//信息头定义宏
#define MAX_CLIENT_NUMS 20  //允许客户端连接的最大数目
#define RECV_HEAD 0         //接受HEAD
#define RECV_BODY 1			//接受BODY

//函数声明
//线程函数，当接受到一个请求就创建一个线程去处理
DWORD WINAPI ThreadFun(LPVOID lpThreadParameter);

//服务器测试函数
BOOL TestSever();

//打印函数
void PrintUser(const TUserInfo *userInformation);

//crtl+c退出信号处理函数
void Signal_Handler(int nSig);

//添加线程到线程列表中
void AddList(CClient *pCClient);		

//把线程从列表中移除,并释放资源
void RemoveList(CClient *pCClient);	