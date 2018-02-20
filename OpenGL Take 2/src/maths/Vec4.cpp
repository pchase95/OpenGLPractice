#include "Vec4.h"

namespace maths
{
	Vec4::Vec4()
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
	}

	Vec4::Vec4(float t_x, float t_y, float t_z, float t_w)
		: x(t_x), y(t_y), z(t_z), w(t_w)
	{
	}

	Vec4::Vec4(const Vec4& v)
		: x(v.x), y(v.y), z(v.z), w(v.w)
	{
	}


	Vec4 Vec4::multiply(const Mat4& m) const
	{
		Vec4 result;

		const float* data[4] {
			&x,
			&y,
			&z,
			&w
		};

		float* res_data[4] {
			&result.x,
			&result.y,
			&result.z,
			&result.w
		};

		for (unsigned char row = 0; row < 4; row++)
		{
			for (unsigned char num = 0; num < 4; num++)
			{
				*res_data[row] += m.getData()[4 * row + num] * *data[num];
			}
		}

		return result;
	}

	Vec4 Vec4::operator*(const Mat4& m) const
	{
		return multiply(m);
	}

	std::ostream& operator<<(std::ostream& os, const Vec4& v)
	{
		os << "x->" << v.x << "\t" <<
			  "y->" << v.y << "\t" <<
			  "z->" << v.z << "\t" <<
			  "w->" << v.w;

		return os;
	}
}
