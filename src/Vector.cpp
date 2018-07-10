#include "Vector.h"

Vector2f::Vector2f()
{
}
Vector2f::Vector2f(Vector2f vec)
		:d(vec.d), v(vec.v)
{
}
Vector2f::Vector2f(Point d, float v)
		:d(d),v(v)
{
}
Vector2f::Vector2f(float ix, float iy, float iv)
		:v(iv)
{
	d.x = ix;
	d.y = iy;
}

Vector2f Vector2f::operator+(Vector2f vec)
{
	Vector2f r;
	r.d.x = d.x + vec.d.x;
	r.d.y = d.y + vec.d.y;
	r.v = v + vec.v;
	return r;
}
Vector2f Vector2f::operator-(Vector2f vec)
{
	Vector2f r;
	r.d.x = x - vec.d.x;
	r.d.y = y - vec.d.y;
	r.v = v - vec.v;
	return r;
}
Vector2f Vector2f::operator*(float f)
{
	Vector2f r;
	r.d = d * f;
	r.v = v * f;
	return r;
}
