#pragma once
#include <iostream>
#include <string>
#include <list>
using namespace std;

typedef string objectStr;
class ConcreteAggregate;
class ConcreteIterator;

//Iterator�������� �ӿ�
class Iterator {

public:
	Iterator();
	virtual~Iterator();
	virtual objectStr firstObjectStr() = 0;
	virtual objectStr nextObjectStr() = 0;
	virtual bool isDone() = 0;
	virtual objectStr currentObjectStr() = 0;
};

//Aggregate�ۼ��� �ӿ�
class Aggregate {

public:
	virtual Iterator *createIterator() = 0;
	virtual ~Aggregate();
};

//ConcreteIterator�����������
class ConcreteIterator : public Iterator {

public:
	ConcreteIterator(ConcreteAggregate *aggregate);
	~ConcreteIterator();
	objectStr firstObjectStr();
	objectStr nextObjectStr();
	bool isDone();
	objectStr currentObjectStr();

private:
	ConcreteAggregate *m_aggregate;	//����ۼ�����
	int m_current;
};

//ConcreteAggregate����ۼ��� �̳� Aggregate
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