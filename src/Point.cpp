#include "Point.h"


PointRec2f::PointRec2f()
{
}
PointRec2f::PointRec2f(PointRec2f p)
		:x(p.x), y(p.y)
{
}
PointRec2f::PointRec2f(float x, float y)
		:x(x), y(y)
{
}
PointRec2f PointRec2f::operator+(PointRec2f p)
{
	PointRec2f r;
	r.x = x + p.x;
	r.y = y + p.y;
	return r;
}
PointRec2f PointRec2f::operator-(PointRec2f p1, PointRec2f p2)
{
	PointRec2f r;
	r.x = p1.x - p2.x;
	r.y = p1.y - p2.y;
	return r;
}
PointRec2f PointRec2f::operator*(float f)
{
	PointRec2f r;
	r.x = x * f;
	r.y = y * f;
}
float PointRec2f::operator%(PointRec2f p)
{
	return sqrt(abs(x - p.x) * abs(x - p.x) + abs(y - p.y) * abs(y - p.y));
}

PointPol2f::PointPol2f()
{
}
PointPol2f::PointPol2f(PointPol2f p)
		:t(p.t), l(p.l)
{
}

PointPol2f::PointPol2f(float t, float l)
		:t(t),l(l)
{
}

PointPol2f PointPol2f::operator+(PointPol2f p)
{
	PointPol2f r;
	r.l = l + p.l;
	r.t = t + p.t;
	return r;
}
PointPol2f PointPol2f::operator-(PointPol2f p1, PointPol2f p2)
{
	PointPol2f r;
	r.l = p1.l - p2.l;
	r.t = p1.t = p2.t;
	return r;
}
PointPol2f PointPol2f::operator*(float f)
{
	PointPol2f r;
	r.t = t * f;
	r.l = l * f;
	return r;
}
float PointPol2f::operator%(PointPol2f p)
{

}


PointPol2f Rec2Pol(PointRec2f p)
{
	float t = tan(p.y / p.x);
	float l = sqrt(p.x * p.x + p.y * p.y);
	PointPol2f res(t, l);
	return res;
}
PointRec2f Pol2Rec(PointPol2f p)
{
	
}
