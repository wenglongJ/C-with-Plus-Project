class Shape
{
public:
	enum ShapeColor { Red, Green, Blue };
	// 所有形状都必须提供一个函数，用来绘出自己。
	virtual void draw(ShapeColor color = Red) const = 0;
};

class Circle : public Shape
{
public:
	Circle() {};
	virtual void draw(ShapeColor color=Green) const;
};

int main() {
	Shape *pc = new Circle;
	// 该代码相当于 pc->draw(Shape::Red)
	pc->draw();

	// new一个Circle对象 | 静态类型Circle | 动态类型Circle.
	Circle *pc1 = new Cirlce;
	// 错误！！不能运行！！
	// 因为参数跟着静态类型走，Circle静态类型的定义并没有缺省值，所以必须要给定参数才可以。
	pc->draw();
	// 正确
	pc->draw(Shape::Blue);
}