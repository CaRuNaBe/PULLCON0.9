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
		static constexpr float PI = 3.14159265358979f;
		static constexpr float DEGREES_180 = 180.0f;
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

}
