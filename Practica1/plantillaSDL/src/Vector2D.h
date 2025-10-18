#pragma once
#include <iostream>

template <class T>
class Vector2D
{
private:
	T x, y;

public:
	Vector2D(){}
	Vector2D(const T& x, const T& y) : x(x), y(y) {}
	~Vector2D() {}
	const T& getX() const { return x; }
	const T& getY() const { return y; }
	void setX(T newX) { x = newX; }
	void setY(T newY) { y = newY; }

	friend Vector2D operator+ (Vector2D r, const Vector2D& l) {
		r.x += l.x; r.y += l.y;
		return r;
	}
	friend Vector2D operator- (Vector2D r, const Vector2D& l) {
		r.x -= l.x; r.y -= l.y;
		return r;
	}

	// Producto escalar
	friend int operator * (const Vector2D& r, const Vector2D& l) {
		return r.x * l.x + r.y * l.y;
	}

	// Producto por escalar
	Vector2D operator * (T s) const { 
		return Vector2D(x*s, y*s);
	}

	// Para debug
	friend std::ostream& operator<< (std::ostream& os, const Vector2D<T>& v) {
		os << v.x << ", " << v.y;
		return os;
	}
};

template <class T>
using Point2D = Vector2D<T>;
