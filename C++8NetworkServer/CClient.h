#pragma once

//�߳��࣬��ʼ��ʱ�����̣߳�����ʱ�Զ��ͷ�������Դ
class CClient
{
public:
	CClient(SOCKET sockClient);
	~CClient();

	BOOL Start();		//��ʼ�߳�
	BOOL Stop();		//ֹͣ�߳�
	unsigned int Run();	//�����߳�
	HANDLE& GetHandle();

private:
	HANDLE m_hTread;            //���
	SOCKET m_sockClient;        //�ͻ����׽���
	BOOL m_bBreak;              //�߳�����
};


