#include "Polar2.h"

namespace math
{
	Polar2::Polar2()
		:radius( 0.0f )
		,theta( 0.0f )
		,centor( 0.0f,0.0f )
	{
	};

	Polar2::Polar2( const Vector2& centor,float radius,float theta )
		:radius( radius )
		,theta( theta )
		,centor( centor )
	{
	};

	Polar2::Polar2( const Vector2& centor,int radius,int theta )
		:radius( static_cast<float> (radius) )
		,theta( static_cast<float> (theta) )
		,centor( centor )
	{
	};

	Polar2::Polar2( const Vector2& vec2,const Vector2& centor,float theta )
		:radius( centor.Length( vec2 ) )
		,theta( theta )
		,centor( centor )
	{
	};

	Vector2 Polar2::ToVector2()
	{
		float x = radius * std::cos( utility::degree_to_radian( theta ) ) + centor.x;
		float y = radius * std::sin( utility::degree_to_radian( theta ) ) + centor.y;
		return Vector2{x,y};
	};

	void Polar2::RadiusIncrement( float fnum )
	{
		radius += fnum;
	};

	void Polar2::ThetaIncrement( float fnum )
	{
		theta += fnum;

	};

	void Polar2::RadiusDecrement( float fnum )
	{
		radius -= fnum;
		if ( radius < 0 )
		{
			radius = 0;
		}
	};

	void Polar2::ThetaDecrement( float fnum )
	{
		theta -= fnum;

	};

	radius_and_phi Polar2::Get()
	{
		auto polar2 = std::make_tuple( radius,theta );
		return polar2;
	}
}
