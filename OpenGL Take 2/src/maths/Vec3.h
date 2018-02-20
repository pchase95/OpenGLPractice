#pragma once

namespace maths
{
	struct Vec3
	{
		float x, y, z;
		Vec3();
		Vec3(float t_x, float t_y, float t_z);
		Vec3(const Vec3& v);
		~Vec3() {}
	};
}