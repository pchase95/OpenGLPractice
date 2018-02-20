#pragma once

namespace maths
{
	struct Vec2
	{
		float x, y;

		Vec2();
		Vec2(float t_x, float t_y);
		Vec2(const Vec2& v);
		~Vec2() {}
	};
}
