#pragma once

class Handle:
{
public:
	Handle();
	Handle(int, int);
	Handle(const Point&);
	Handle(const Handle&);
	Handle& operator=(const Handle&);
	~Handle();

	int x() const;
	Handle& x(int);
	int y() const;
	Handle& y(int);

private:

};