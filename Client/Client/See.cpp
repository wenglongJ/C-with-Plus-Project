class Shape
{
public:
	enum ShapeColor { Red, Green, Blue };
	// ������״�������ṩһ����������������Լ���
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
	// �ô����൱�� pc->draw(Shape::Red)
	pc->draw();

	// newһ��Circle���� | ��̬����Circle | ��̬����Circle.
	Circle *pc1 = new Cirlce;
	// ���󣡣��������У���
	// ��Ϊ�������ž�̬�����ߣ�Circle��̬���͵Ķ��岢û��ȱʡֵ�����Ա���Ҫ���������ſ��ԡ�
	pc->draw();
	// ��ȷ
	pc->draw(Shape::Blue);
}