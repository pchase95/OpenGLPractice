#pragma once
#include <array>
#include <ostream>
#include "Vec3.h"
#include "Vec4.h"

namespace maths
{
#define MAT4_SIZE 16
	struct Vec4;

	class Mat4
	{
	private:
		std::array<float, MAT4_SIZE> data;

	public:
		Mat4();
		Mat4(float diagonal);
		Mat4(const Mat4& m);
		Mat4(std::array<float, MAT4_SIZE> t_data);
		Mat4(float* t_data);
		~Mat4() {}

		Mat4 multiply(const Mat4& m) const;
		Mat4 operator*(const Mat4& m) const;
		Vec4 operator*(const Vec4& v) const;

		static Mat4 Identity();
		static Mat4 Transform(const Vec3& translation);
		static Mat4 Scale(const Vec3& scalar);
		static Mat4 Rotate(const float& angle, const Vec3& axis);
		
		inline std::array<float, 16> getData() const { return data; }
		inline const float* Get() const { return data.data(); }
		friend std::ostream& operator<<(std::ostream& os, const Mat4& m);
	};
}
