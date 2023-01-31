#include "MenuComponent.h"
#include "watress.h"

int main()
{
	MenuComponent* pancakeHouseMenu = new Menu("PANCAKE HOUSE MENU", "Breakfast");
	MenuComponent* dinerMenu = new Menu("DINER MENU", "Lunch");
	MenuComponent* cafeMenu = new Menu("CAFE MENU", "Diner");
	MenuComponent* dessertMenu = new Menu("DESSERT MENU", "Desert of course");

	MenuComponent* allMenus = new Menu("ALL MENUS", "All menus combined");

	allMenus->add(pancakeHouseMenu);
	allMenus->add(dinerMenu);
	allMenus->add(cafeMenu);

	pancakeHouseMenu->add(new MenuItem("K&B's Pancake Breakfast", "Pancakes with scrambled eggs, and toast", true, 2.99));
	pancakeHouseMenu->add(new MenuItem("Regular Pancake Breakfast", "Pancake with fried eggs， sausage", false, 2.99));
	pancakeHouseMenu->add(new MenuItem("Blueberry Pancake", "Pancake made with fresh blueberries", true, 3.49));
	pancakeHouseMenu->add(new MenuItem("Waffles", "Waffles, with your cchoice of blueberries or strawberries", true, 3.59));

	dinerMenu->add(new MenuItem("Vegtarian BLT", "(Fakin) Bacon with lettuce & tomato on whole wheat", true, 2.99));
	dinerMenu->add(new MenuItem("BLT", "Bacon with lettuce & tomato on while wheat", false, 2.99));
	dinerMenu->add(new MenuItem("Soup of the day", "Soup of the day,with a side of potato aalad", false, 3.29));
	dinerMenu->add(new MenuItem("Hotdog", "A hot dog,with saurkraut, relish, onions, topped with cheese", false, 3.05));
	dinerMenu->add(new MenuItem("Steamed Veggies and Brown Rice", "Steamed vegetables over brown rice", true, 3.99));
	dinerMenu->add(new MenuItem("Pasta", "Spaghetti with Marinara Sauce, and a slice of sourdough bread", true, 3.89));

	dinerMenu->add(dessertMenu);//在晚餐菜单中加入三个甜点菜单，
	dessertMenu->add(new MenuItem("Apple Pie", "Apple pie with a flkey crust,topped with vanila ice cream", true, 1.59));
	dessertMenu->add(new MenuItem("Cheesecake", "Creamy New York cheesecake, with a chocolate graham crust", true, 1.99));
	dessertMenu->add(new MenuItem("Sorbet", "A scoop of raspberry and ascoop of lime", true, 1.89));

	cafeMenu->add(new MenuItem("Veggie Burger and Air Fries", "Veggie burger on a whole wheat bun, lettuce, tomato, and fries", true, 3.99));
	cafeMenu->add(new MenuItem("Soup of the day", "A cup of the soup of the day, with a side salad", false, 3.69));
	cafeMenu->add(new MenuItem("Burrito", "A large burrito, with whole pinto beans, salse, guacamol", true, 4.29));

	Watress* waitress = new Watress(allMenus);
	waitress->printMenu();

	getchar();
	return 0;
}