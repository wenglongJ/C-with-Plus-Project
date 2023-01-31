#include "Header.h"

Iterator::Iterator()
{

}

Iterator::~Iterator()
{
	cout << "Iterator::~Iterator()" << endl;
}

Aggregate::~Aggregate()
{
	cout << "Aggregate::~Aggregate()" << endl;
}

ConcreteIterator::ConcreteIterator(ConcreteAggregate *aggregate)
{
	m_aggregate = aggregate;
	m_current = 0;
}

ConcreteIterator::~ConcreteIterator()
{
	cout << "ConcreteIterator::~ConcreteIterator()" << endl;
	delete m_aggregate;
}

objectStr ConcreteIterator::firstObjectStr()
{
	return m_aggregate->getItem(0);
}

objectStr ConcreteIterator::nextObjectStr()
{
	m_current++;
	if (m_current >= m_aggregate->getListCount()) {

		return m_aggregate->getItem(m_aggregate->getListCount() - 1);
	}
	return m_aggregate->getItem(m_current);
}

bool ConcreteIterator::isDone()
{
	return m_current >= m_aggregate->getListCount() ? true : false;
}

objectStr ConcreteIterator::currentObjectStr()
{
	return m_aggregate->getItem(m_current);
}

ConcreteAggregate::~ConcreteAggregate()
{
	cout << "ConcreteAggregate::~ConcreteAggregate()" << endl;
	m_items.clear();
}

Iterator * ConcreteAggregate::createIterator()
{
	return new ConcreteIterator(this);
}

int ConcreteAggregate::getListCount()
{
	return this->m_items.size();
}

objectStr ConcreteAggregate::getItem(const int &sub)
{
	int i = 0;
	for (list<objectStr>::iterator it = m_items.begin(); it != m_items.end(); it++) {

		if (i == sub) {

			return (*it);
		}

		i++;
	}
	return "";
}

void ConcreteAggregate::addItem(objectStr item)
{
	m_items.push_back(item);
}

