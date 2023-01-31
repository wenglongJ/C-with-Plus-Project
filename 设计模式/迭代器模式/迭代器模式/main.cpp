#include "Header.h"
#include <vector>

//int main() {
//
//	ConcreteAggregate *a = new ConcreteAggregate();
//
//	a->addItem("球球");
//	a->addItem("腿腿");
//	a->addItem("米线");
//	a->addItem("闰土");
//	a->addItem("猪小明");
//	a->addItem("妹爷");
//	a->addItem("蘑菇头");
//	a->addItem("锅盖");
//
//	Iterator *iter = new ConcreteIterator(a);
//
//	while (!iter->isDone()) {
//
//		cout << iter->currentObjectStr() << "买票了！！！" << endl;
//		iter->nextObjectStr();
//	}
//
//	delete a;
//
//	getchar();
//	return 0;
//}



//例子2
class Menus {
public:
	virtual void* createIterator() = 0;
};


class MenuItem {

private:
	string name;
	string description;
	bool vegetarian;
	double price;

public:
	MenuItem() {}
	MenuItem(string m_name, string m_description, bool m_vegetarian, double m_price) :
		name(m_name), description(m_description), vegetarian(m_vegetarian), price(m_price) {}

	string getName() {
		return name;
	}

	string getDescription() {
		return description;
	}

	double getPrice() {
		return price;
	}

	bool isVegetarian() {
		return vegetarian;
	}
};

class m_iterator {
public:
	virtual bool hasNext() = 0;
	virtual MenuItem* next() = 0;
};

class DinerMenuIterator :public m_iterator {
public:
	DinerMenuIterator(MenuItem** m_menuItems, int m_size) :menuItems(m_menuItems), length(m_size) {
	}
	~DinerMenuIterator() {
		if (menuItems) {
			delete menuItems;
			menuItems = nullptr;
		}
	}

	virtual bool hasNext() {

		if (length == 0 || position >= length) {
			return false;
		}
		return true;
	}

	virtual MenuItem* next() {
		if (position < length)
			return menuItems[position++];
	}


private:
	int length = 0;
	int position = 0;
	MenuItem** menuItems;
};


class PancakeMenuIterator :public m_iterator {
public:
	PancakeMenuIterator(list<MenuItem>& m_menuItems) :menuItems(m_menuItems) {
		start = menuItems.begin();
	}

	virtual bool hasNext() {

		if (start == menuItems.end()) {
			return false;
		}
		return true;
	}

	virtual MenuItem* next() {
		if (start != menuItems.end()) {
			MenuItem* temp = &(*start);
			++start;
			return temp;
		}
	}


private:
	list<MenuItem> menuItems;
	list<MenuItem>::iterator start;

};


class DinerMenu :public Menus {
private:
	static int MAX_ITEMS;
	int numberOfItems = -1;
	MenuItem** menuIems = nullptr;

public:
	DinerMenu() {
		menuIems = new MenuItem*[MAX_ITEMS];
		addItem("Vegetarian BLT", "Bacon with lettuce", true, 2.99);
		addItem("Soup of the day", "Soup of the day , with a side of potato salad", false, 3.99);

	}

	void addItem(string name, string description, bool vegetarian, double price) {
		if (numberOfItems < MAX_ITEMS) {
			menuIems[++numberOfItems] = new MenuItem(name, description, vegetarian, price);
		}
	}

	int getSize() {
		return numberOfItems;
	}

	MenuItem** getMenuItems() {
		return menuIems;
	}
	~DinerMenu() {
		if (menuIems) {
			delete[] menuIems;
			menuIems = nullptr;
		}
	}


	virtual void* createIterator() {

		return new DinerMenuIterator(menuIems, numberOfItems + 1);
	}


};

int DinerMenu::MAX_ITEMS = 6;

class PancakeHouseMenu :public Menus {

private:
	list<MenuItem> menuItems;
public:

	PancakeHouseMenu() {
		addItem("Pancake Breakfast", "Pancakes with scrambled eggs", true, 4.99);
		addItem("Regular Breakfast", "Pancakes made with fresh blueberries", true, 5.99);
	}

	void addItem(string name, string description, bool vegetarian, double price) {
		menuItems.push_back(MenuItem(name, description, vegetarian, price));
	}

	list<MenuItem> getMenuItems() {
		return menuItems;
	}
	virtual void* createIterator() {

		return new PancakeMenuIterator(menuItems);
	}
};



int main() {

	vector<Menus*> menus; //总的菜单容器

	DinerMenu* dinnermenu = new DinerMenu;
	menus.push_back(dinnermenu); //加入菜单
	PancakeHouseMenu* pancakemenu = new PancakeHouseMenu;
	menus.push_back(pancakemenu);

	for (int i = 0; i < menus.size(); ++i) {  //遍历每个菜单的菜

		m_iterator* pointer = (m_iterator*)menus[i]->createIterator();

		while (pointer->hasNext()) {
			MenuItem* menuitem = pointer->next();
			cout << menuitem->getName() << " " << menuitem->getPrice() << endl;
		}

		cout << endl << endl;

	}


	system("pause");
	return 0;

}
