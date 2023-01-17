#include <iostream>
#include <string>
//���������-����
class Beverage
{
public:
	Beverage() :m_description("Unknown Beverage")
	{

	}
	virtual std::string getDescription() { return m_description; }
	virtual double cost() = 0;
protected:
	std::string m_description;
};

//����װ������-���ϣ��̳���������
class CondimentDecorator :public Beverage
{
public:
	CondimentDecorator(Beverage* berverge)
		:m_beverage(berverge)
	{

	}
	~CondimentDecorator()
	{
		delete m_beverage;
	}
	virtual std::string getDescription() = 0;//����ɴ��麯������Ϊ��ǿ������ʵ����ʱ����ʵ������
protected:
	Beverage* m_beverage;
};

//�����������
class DarkRoast :public Beverage
{
public:
	DarkRoast()
	{
		m_description = "DarkRoast";
	}
	double cost()
	{
		return 2.99;
	}
};

class Espresso :public Beverage
{
public:
	Espresso()
	{
		m_description = "Espresso";
	}
	double cost()
	{
		return 1.99;
	}
};

class HouseBlend :public Beverage
{
public:
	HouseBlend()
	{
		m_description = "HouseBlend";
	}
	double cost()
	{
		return 0.89;
	}
};

//��������װ����
class Mocha :public CondimentDecorator
{
public:
	Mocha(Beverage* beverage) :CondimentDecorator(beverage)
	{
	}

	std::string getDescription()
	{
		return  m_beverage->getDescription() + " Mocha";
	}

	double cost()
	{
		return 0.2 + m_beverage->cost();
	}
};


class Milk :public CondimentDecorator
{
public:
	Milk(Beverage* beverage) :CondimentDecorator(beverage)
	{

	}


	std::string getDescription()
	{
		return  m_beverage->getDescription() + " Milk";
	}

	double cost()
	{
		return 0.5 + m_beverage->cost();
	}
};

//���Դ���
int main()
{
	//���ӵ��ϵ�Espresso
	Beverage* beverage = new Espresso();
	std::cout << beverage->getDescription() << " ��" << beverage->cost() << std::endl;

	//��˫��Ħ�������ݵ�DarkRoast
	Beverage* beverage2 = new DarkRoast();
	beverage2 = new Mocha(beverage2);
	beverage2 = new Mocha(beverage2);
	beverage2 = new Milk(beverage2);
	std::cout << beverage2->getDescription() << " ��" << beverage2->cost() << std::endl;

	//��˫�����ݵĺ�һ��Ħ����HouseBlend
	Beverage* beverage3 = new HouseBlend();
	beverage3 = new Mocha(beverage3);
	beverage3 = new Milk(beverage3);
	beverage3 = new Milk(beverage3);
	std::cout << beverage3->getDescription() << " ��" << beverage3->cost() << std::endl;

	system("pause");
	delete beverage;
	delete beverage2;
	delete beverage3;
}