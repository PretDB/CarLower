#include "Point.h"
class Vector2f
{
public:
	Point d;
	float v = 0.0;


	Vector2f();
	Vector2f(Vector2f v);
	Vector2f(Point d, float v);
	Vector2f(float x, float y, float v);

	Vector2f operator+(Vector2f v);
	Vector2f operator-(Vector2f v);
	Vector2f operator*(float f);
};
