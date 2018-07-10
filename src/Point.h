PointPol2f Rec2Pol(PointRec2f p);
PointRec2f Pol2Rec(PointPol2f p);


class PointRec2f
{
public:
		float x = 0.0;
		float y = 0.0;

		PointRec2f();
		PointRec2f(PointRec2f p);
		PointRec2f(float x, float y);

		PointPol2f ToPol();

		PointRec2f operator+(PointRec2f p);
		PointRec2f operator-(PointRec2f p);
		PointRec2f operator*(float f);
		float operator%(PointRec2f p);
};

class PointPol2f
{
public:
		float l = 0.0;
		float t = 0.0;

		PointPol2f();
		PointPol2f(PointPol2f p);
		PointPol2f(float x, float y);

		PointRec2f ToRec();

		PointPol2f operator+(PointPol2f p);
		PointPol2f operator-(PointPol2f p);
		PointPol2f operator*(float f);
		float operator%(PointPol2f p);
};


