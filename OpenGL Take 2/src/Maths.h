#pragma once

namespace Maths
{
	struct Vec2
	{
		float x, y;

		Vec2()
			: x(0.0f), y(0.0f)
		{
		}

		Vec2(float t_x, float t_y)
			: x(t_x), y(t_y)
		{
		}

		Vec2(Vec2 const& v)
			: x(v.x), y(v.y)
		{
		}

		~Vec2() {}
	};

	struct Vec3
	{
		float x, y, z;

		Vec3()
			: x(0.0f), y(0.0f), z(0.0f)
		{
		}

		Vec3(float t_x, float t_y, float t_z)
			: x(t_x), y(t_y), z(t_z)
		{
		}

		Vec3(Vec3 const& v)
			: x(v.x), y(v.y), z(v.z)
		{
		}

		~Vec3() {}
	};

	struct Vec4
	{
		float x, y, z, a;

		Vec4()
			: x(0.0f), y(0.0f), z(0.0f), a(0.0f)
		{
		}

		Vec4(float t_x, float t_y, float t_z, float t_a)
			: x(t_x), y(t_y), z(t_z), a(t_a)
		{
		}

		Vec4(Vec4 const& v)
			: x(v.x), y(v.y), z(v.z), a(v.a)
		{
		}

		~Vec4() {}
	};
}
