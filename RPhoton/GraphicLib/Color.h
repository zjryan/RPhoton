#ifndef ZJR_COLOR
#define ZJR_COLOR

#include "./Maths.h"

using namespace Math;

class Color
{
public:
	struct _RGB_
	{
		char R;
		char G;
		char B;

		_RGB_(char r, char g, char b) : R(r), G(g), B(b) {}
	};

	float				r;
	float				g;
	float				b;

	Color();
	Color(float c);
	Color(float _r, float _g, float _b);
	Color(const Color &c);
	~Color();

	Color				operator*(const Color &c) const;
	Color				operator*(float f) const;
	Color				operator/(float f) const;
	Color				operator+(const Color &c) const;

	Color&				operator=(const Color &rhs);
	Color&				operator*=(const Color &c);
	Color&				operator*=(float f);
	Color&				operator/=(float f);
	Color&				operator+=(const Color &c);

	_RGB_				Standlize() const;
};

namespace Colors
{
	const Color Black			(0.00f);
	const Color White			(1.00f);
	const Color Grey			(0.25f);
	const Color Red				(1.00f, 0.00f, 0.00f);
	const Color Blue			(0.00f, 0.00f, 1.00f);
	const Color Yellow			(1.00f, 1.00f, 0.00f);
	const Color Brown			(0.71f, 0.40f, 0.16f);
	const Color DarkGreen		(0.00f, 0.41f, 0.41f);
	const Color Orange			(1.00f, 0.75f, 0.00f);
	const Color Green			(0.00f, 0.60f, 0.30f);
	const Color LightGreen		(0.65f, 1.00f, 0.30f);
	const Color DarkYellow		(0.61f, 0.61f, 0.00f);
	const Color LightPurple		(0.65f, 0.30f, 1.00f);
	const Color DarkPurple		(0.50f, 0.00f, 1.00f);
}

#endif
