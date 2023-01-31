#pragma once
//�ͻ��ڴ��Ľӿڣ�Ŀ������Ǿ���Ļ��߳�����࣬Ҳ�����ǽӿ�
class Target {

public:
	virtual void request();
	virtual ~Target();
};

//��Ҫ�������
class Adaptee {

public:
	void specificRequest();
};

//ͨ���ڲ���װһ��Adaptee���󣬰�Դ�ӿ�ת��ΪĿ��ӿ�
class Adapter : public Target {

public:
	void request();
	~Adapter();
	Adapter();

private:
	Adaptee *adaptee;
};