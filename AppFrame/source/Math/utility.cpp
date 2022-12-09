#include <random>
#include <cmath>
#include "vector4.h"
#include "utility.h"

namespace
{
	std::random_device seed_gen;
	std::mt19937_64 random(seed_gen());
}

namespace math
{
	int utility::get_random(const int min,const int max)
	{
		std::uniform_int_distribution<int>  distr(min,max);
		return distr(random);
	}
	// ベクトルの行列変換
	Vector2 Vector2::Transform(const Vector2& vec,const Matrix3& mat,float w)
	{
		return {
			vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + w * mat.m[2][0],
			vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + w * mat.m[2][1],
		};
	}
	// 二つの値の大きい値を取得
	template <typename T>
	T Max(const T& a,const T& b)
	{
		return (a < b ? b : a);
	}
	// 二つの値の小さい値を取得
	template <typename T>
	T Min(const T& a,const T& b)
	{
		return (a < b ? a : b);
	}
	// 二つの値の間でクランプする
	template <typename T>
	T Clamp(const T& value,const T& lower,const T& upper)
	{
		return Min(upper,Max(lower,value));
	}
}
