#pragma once
#include <tuple>
#include"vector2.h"
#include"matrix33.h"
namespace math
{

	class vector4;

	using plane = std::tuple<vector4/*point*/,vector4/*normal*/>;


	class utility
	{
	public:
		static constexpr float DEGREES_ZERO = 0.0f;
		static constexpr float DEGREES_180 = 180.0f;
		static constexpr float DEGREES_360 = DEGREES_180 * 2.0f;
		static constexpr float PI = 3.14159265358979f;
		static constexpr float RADIANS_ZERO = 0.0f;
		static constexpr float TwoPi = PI * 2.0f;
		static constexpr float PiOver2 = PI / 2.0f;

		static float degree_to_radian( float degree )
		{
			return degree * PI / DEGREES_180;
		}

		static float radian_to_degree( float radion )
		{
			return radion * DEGREES_180 / PI;
		}

		static int get_random( const int min,const int max );
		static bool get_random()
		{
			return get_random( 1,2 ) == 1 ? true : false;
		}


	private:
		utility() = default;
	};

	// 二つの値の大きい値を取得
	template <typename T>
	T Max( const T& a,const T& b )
	{
		return (a < b ? b : a);
	}
	// 二つの値の小さい値を取得
	template <typename T>
	T Min( const T& a,const T& b )
	{
		return (a < b ? a : b);
	}
	// 二つの値の間でクランプする
	template <typename T>
	T Clamp( const T& value,const T& lower,const T& upper )
	{
		return Min( upper,Max( lower,value ) );
	}
	template <typename T>
	T Sign( const T& num )
	{
		return (num > 0) - (num < 0);
	}
	template <typename T>
	T Step( const T& num )
	{
		return (num >= 0);
	}
}
