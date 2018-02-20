#pragma once
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>

namespace maths
{
	static float toRadians(float degrees)
	{
		return degrees * ((float)M_PI / 180.0f);
	}

	static float toDegrees(float radians)
	{
		return radians * (180.0f / (float)M_PI);
	}
}
