#pragma once

//线程类，初始化时创建线程，析构时自动释放所有资源
class CClient
{
public:
	CClient(SOCKET sockClient);
	~CClient();

	BOOL Start();		//开始线程
	BOOL Stop();		//停止线程
	unsigned int Run();	//启动线程
	HANDLE& GetHandle();

private:
	HANDLE m_hTread;            //句柄
	SOCKET m_sockClient;        //客户端套接字
	BOOL m_bBreak;              //线程运行
};


