#ifndef ZJR_MATHS_
#define ZJR_MATHS_

#include <math.h>
#define max(a, b) ((a > b) ? a : b)
#define min(a, b) ((a < b) ? a : b)

const double _PI			= 3.1415926535897932384;
const double _TWO_PI		= 6.2831853071795864769;
const double _PI_ON_180		= 0.0174532925199432957;
const double _180_ON_PI		= 57.29577951308232087;
const double _invPI			= 0.3183098861837906715;
const double _invTWO_PI		= 0.1591549430918953358;

namespace Math
{
	inline bool floatEqual(float a, float b)
	{
		return fabs(a - b) < 0.0001;
	}

	inline void swap(float &a, float &b)
	{
		float temp = a;
		a = b;
		b = temp;
	}

	inline float radians(float angle)
	{
		return _PI_ON_180 * angle;
	}

	inline float angles(float radian)
	{
		return _180_ON_PI * radian;
	}

	inline float lerp(float t, float v1, float v2)
	{
		return (1.0f - t) * v1 + t * v2;
	}

	inline float clamp(float val, float low, float high)
	{
		if (val < low)
		{
			return low;
		}
		else if (val > high)
		{
			return high;
		}
		else
		{
			return val;
		}
	}

	inline bool quadratic(float A, float B, float C, float &t0, float &t1)
	{
		float discrim = B * B - 4.0f * A * C;
		if (discrim < 0.0f)
		{
			return false;
		}

		float rootDiscrim = sqrtf(discrim);
		float q;
		if (B < 0)
		{
			q = -0.5f * (B - rootDiscrim);
		}
		else
		{
			q = -0.5f * (B + rootDiscrim);
		}

		t0 = q / A;
		t1 = C / q;
		if (t0 > t1) swap(t0, t1);
		return true;
	}
}


#endif
