#pragma once
#include <ostream>
#include "Mat4.h"
namespace maths
{
	class Mat4;

	struct Vec4
	{
		float x, y, z, w;
		Vec4();
		Vec4(float t_x, float t_y, float t_z, float t_w);
		Vec4(const Vec4& v);
		~Vec4() {}

		Vec4 multiply(const Mat4& m) const;
		Vec4 operator*(const Mat4& m) const;

		friend std::ostream& operator<<(std::ostream& os, const Vec4& v);
	};
}