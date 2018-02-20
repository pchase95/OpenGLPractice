#include "Vec2.h"

namespace maths
{
	Vec2::Vec2()
		: x(0.0f), y(0.0f)
	{
	}

	Vec2::Vec2(float t_x, float t_y)
		: x(t_x), y(t_y)
	{
	}

	Vec2::Vec2(const Vec2& v)
		: x(v.x), y(v.y)
	{
	}
}
