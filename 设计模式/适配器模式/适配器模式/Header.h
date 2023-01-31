#pragma once
//客户期待的接口，目标可以是具体的或者抽象的类，也可以是接口
class Target {

public:
	virtual void request();
	virtual ~Target();
};

//需要适配的类
class Adaptee {

public:
	void specificRequest();
};

//通过内部包装一个Adaptee对象，把源接口转换为目标接口
class Adapter : public Target {

public:
	void request();
	~Adapter();
	Adapter();

private:
	Adaptee *adaptee;
};