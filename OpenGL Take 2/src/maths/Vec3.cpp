#include "Vec3.h"

namespace maths
{
	Vec3::Vec3()
		: x(0.0f), y(0.0f), z(0.0f)
	{
	}

	Vec3::Vec3(float t_x, float t_y, float t_z)
		: x(t_x), y(t_y), z(t_z)
	{
	}

	Vec3::Vec3(const Vec3& v)
		: x(v.x), y(v.y), z(v.z)
	{
	}
}
