#pragma once
#include "vector2.h"
#include <array>

namespace math
{
	// 3次行列クラス
	class Matrix3
	{
	public:
		// 3列×3行
		std::array<std::array<float,3>,3> m;

		constexpr Matrix3()
		{
			*this = Matrix3::Identity;
		}
		constexpr Matrix3
		(float m00,float m01,float m02,								
		 float m10,float m11,float m12,								
		 float m20,float m21,float m22) noexcept
			: m{m00, m01, m02,
			m10, m11, m12,
			m20, m21, m22}
		{}
		friend static Vector2 Vector2::Transform(const Vector2& vec,const Matrix3& mat,float w);

		// 行列の乗算
		friend Matrix3 operator*(const Matrix3& l,const Matrix3& r)
		{
			return {
				// row 0
				l.m[0][0] * r.m[0][0] + l.m[0][1] * r.m[1][0] + l.m[0][2] * r.m[2][0],
				l.m[0][0] * r.m[0][1] + l.m[0][1] * r.m[1][1] + l.m[0][2] * r.m[2][1],
				l.m[0][0] * r.m[0][2] + l.m[0][1] * r.m[1][2] + l.m[0][2] * r.m[2][2],
				// row 1
				l.m[1][0] * r.m[0][0] + l.m[1][1] * r.m[1][0] + l.m[1][2] * r.m[2][0],
				l.m[1][0] * r.m[0][1] + l.m[1][1] * r.m[1][1] + l.m[1][2] * r.m[2][1],
				l.m[1][0] * r.m[0][2] + l.m[1][1] * r.m[1][2] + l.m[1][2] * r.m[2][2],
				// row 2
				l.m[2][0] * r.m[0][0] + l.m[2][1] * r.m[1][0] + l.m[2][2] * r.m[2][0],
				l.m[2][0] * r.m[0][1] + l.m[2][1] * r.m[1][1] + l.m[2][2] * r.m[2][1],
				l.m[2][0] * r.m[0][2] + l.m[2][1] * r.m[1][2] + l.m[2][2] * r.m[2][2],
			};
		}
		Matrix3& operator*=(const Matrix3& right)
		{
			*this = *this * right;
			return *this;
		}

		// 回転行列の作成
		static Matrix3 CreateRotation(float theta)
		{
			using std::sin;	using std::cos;
			return {
				cos(theta), sin(theta), 0.0f,
				-sin(theta), cos(theta), 0.0f,
				0.0f, 0.0f, 1.0f,
			};
		}

		// 拡縮行列の作成
		static Matrix3 CreateScale(float xScale,float yScale)
		{
			return {
				xScale, 0.0f, 0.0f,
				0.0f, yScale, 0.0f,
				0.0f, 0.0f, 1.0f,
			};
		}
		static Matrix3 CreateScale(const Vector2& scaleVector)
		{
			return CreateScale(scaleVector.x,scaleVector.y);
		}
		static Matrix3 CreateScale(float scale)
		{
			return CreateScale(scale,scale);
		}

		// 平行移動行列の作成
		static Matrix3 CreateTranslation(const Vector2& trans)
		{
			return {
				1.0, 0.0, 0.0,
				0.0, 1.0, 0.0,
				trans.x, trans.y, 1.0,
			};
		}

		// 単位行列
		static const Matrix3 Identity;
	};
}
