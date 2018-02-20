#include "Mat4.h"
#include "Utils.h"

namespace maths
{
	Mat4::Mat4()
	{
		data.fill(0.0f);
	}

	Mat4::Mat4(float diagonal)
		: data({
			diagonal, 0.0f, 0.0f, 0.0f,
			0.0f, diagonal, 0.0f, 0.0f,
			0.0f, 0.0f, diagonal, 0.0f,
			0.0f, 0.0f, 0.0f, diagonal
		  })
	{
	}

	Mat4::Mat4(const Mat4& m)
		: data(m.data)
	{
	}

	Mat4::Mat4(float* t_data)
	{
		size_t size = MAT4_SIZE * sizeof(float);
		memcpy_s(data.data(), size, t_data, size);
	}

	Mat4::Mat4(std::array<float, MAT4_SIZE> t_data)
		: data(t_data)
	{
	}

	Mat4 Mat4::multiply(const Mat4& m) const
	{
		Mat4 result;
		// Go through each row/column
		for (unsigned char row = 0; row < 4; row++)
		{
			for (unsigned char col = 0; col < 4; col++)
			{
				float value = 0.0f;
				for (unsigned char num = 0; num < 4; num++)
				{
					value += data[4 * row + num] * m.data[4 * num + col];
				}
				result.data[4 * row + col] = value;
			}
		}
		return result;
	}

	Mat4 Mat4::operator*(const Mat4& m) const
	{
		return multiply(m);
	}

	Vec4 Mat4::operator*(const Vec4& v) const
	{
		return v.multiply(*this);
	}

	Mat4 Mat4::Identity()
	{
		return Mat4(1.0f);
	}

	Mat4 Mat4::Transform(const Vec3& transform)
	{
		Mat4 result = Identity();

		result.data[0 + 3 * 4] = transform.x;
		result.data[1 + 3 * 4] = transform.y; 
		result.data[2 + 3 * 4] = transform.z; 

		return result;
	}

	Mat4 Mat4::Scale(const Vec3& scalar)
	{
		Mat4 result = Identity();

		result.data[0 + 0 * 4] = scalar.x;
		result.data[1 + 1 * 4] = scalar.y;
		result.data[2 + 2 * 4] = scalar.z;

		return result;
	}

	Mat4 Mat4::Rotate(const float& angle, const Vec3& axis)
	{
		/* x-axis */
		Mat4 m_x = Mat4::Identity();
		if (axis.x != 0.0f)
		{
			float r_x = toRadians(axis.x * angle);
			float cos_x = cos(r_x);
			float sin_x = sin(r_x);
			m_x.data[1 + 1 * 4] =  cos_x;
			m_x.data[1 + 2 * 4] = -sin_x;
			m_x.data[2 + 1 * 4] =  sin_x;
			m_x.data[2 + 2 * 4] =  cos_x;
		}
		/**********/

		/* y-axis */
		Mat4 m_y = Mat4::Identity();
		if (axis.y != 0.0f)
		{
			float r_y = toRadians(axis.y * angle);
			float cos_y = cos(r_y);
			float sin_y = sin(r_y);
			m_y.data[0 + 0 * 4] =  cos_y;
			m_y.data[0 + 2 * 4] =  sin_y;
			m_y.data[2 + 0 * 4] = -sin_y;
			m_y.data[2 + 2 * 4] =  cos_y;
		}
		/**********/


		/* z-axis */
		Mat4 m_z = Mat4::Identity();
		if (axis.z != 0.0f)
		{
			float r_z = toRadians(axis.z * angle);
			float cos_z = cos(r_z);
			float sin_z = sin(r_z);
			m_z.data[0 + 0 * 4] =  cos_z;
			m_z.data[0 + 1 * 4] = -sin_z;
			m_z.data[1 + 0 * 4] =  sin_z;
			m_z.data[1 + 1 * 4] =  cos_z;
		}
		/**********/
		return m_x * m_y * m_z;
	}

	std::ostream& operator<<(std::ostream& os, const Mat4& m)
	{
		os << "----------- Mat4 -----------\n";
		for (int x = 0; x < MAT4_SIZE; x++)
		{
			os << m.data[x] << "\t";
			if ((x + 1) % 4 == 0) os << "\n";
		}
		os << "----------------------------";

		return os;
	}
}