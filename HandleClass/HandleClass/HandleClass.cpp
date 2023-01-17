#include<iostream>
using namespace std;

class Point {
public:
	Point() :xval(0) {}
	Point(int _x) :xval(_x) {}
	Point &x(int _x) { xval = _x; return *this; }
	int x() { return xval; }
private:
	int xval;
};

class UPoint {
	// 所有成员为私有
	friend class Handle;
	UPoint() :u(1) {}
	UPoint(int _x) :u(1), P(_x) {}
	UPoint(Point &p0) :u(1), P(p0) {}
	int u;
	Point P;
};

class Handle {
public:
	Handle() :up(new UPoint) {}
	Handle(int _x) :up(new UPoint(_x)) {}
	Handle(Point &p0) :up(new UPoint(p0)) {}
	Handle(Handle &h) :up(h.up) { up->u++; }
	~Handle() { if (0 == --up->u) delete up; }
	Handle& operator=(const Handle &h)
	{
		if (0 == --up->u)
			delete up;

		up = h.up;
		up->u++;
	}
	int x()
	{
		return up->P.x();
	}
#if 1	
	// 指针语义
	Handle& x(int _x)
	{
		up->P.x(_x);
		return *this;
	}

#else
	// 值语义
	Handle& x(int _x)
	{
		if (1 != up->u)
		{
			up->u--;
			up = new UPoint(up->P);
		}
		up->P.x(_x);
		return *this;
	}
#endif
private:
	UPoint *up;
};


int main()
{
	Handle h(3);
	Handle h1 = h;
	h1.x(5);
	cout << "h.x = " << h.x();
	getchar();
	return 0;
}