#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;

typedef string objectStr;
class ConcreteAggregate;
class ConcreteIterator;

//Iterator迭代器类 接口
class Iterator {

public:
	Iterator();
	virtual~Iterator();
	virtual objectStr firstObjectStr() = 0;
	virtual objectStr nextObjectStr() = 0;
	virtual bool isDone() = 0;
	virtual objectStr currentObjectStr() = 0;
};

//Aggregate聚集类 接口
class Aggregate {

public:
	virtual Iterator *createIterator() = 0;
	virtual ~Aggregate();
};

//ConcreteIterator具体迭代器类
class ConcreteIterator : public Iterator {

public:
	ConcreteIterator(ConcreteAggregate *aggregate);
	~ConcreteIterator();
	objectStr firstObjectStr();
	objectStr nextObjectStr();
	bool isDone();
	objectStr currentObjectStr();

private:
	ConcreteAggregate *m_aggregate;	//具体聚集对象
	int m_current;
};

//ConcreteAggregate具体聚集类 继承 Aggregate
class ConcreteAggregate : public Aggregate {

public:
	~ConcreteAggregate();
	Iterator *createIterator();
	int getListCount();
	objectStr getItem(const int &sub);
	void addItem(objectStr item);

private:
	list<objectStr> m_items;
};