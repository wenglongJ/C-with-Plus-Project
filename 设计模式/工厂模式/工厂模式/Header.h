#pragma once
#ifndef HEAD_H
#define HEAD_H


//�������
class Operation {

public:
	double m_numberA;
	double m_numberB;
	virtual double getResult();
};

class AddOperation : public Operation {

public:
	AddOperation();
	double getResult();
};

class MultiOperation : public Operation {

public:
	MultiOperation();
	double getResult();
};

//�������

class IFactory {

public:
	virtual Operation *createOperation();
};

class AddFactory : public IFactory {

public:
	Operation *createOperation();
};

class MultiFactory : public IFactory {

public:
	Operation *createOperation();
};


#endif	//HEAD_H