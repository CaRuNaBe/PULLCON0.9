#pragma once
#include <cmath>
#include "Vector2.h"
#include "utility.h"
namespace math
{
	using radius_and_phi = std::tuple<float,float>;
	class Vector2;
	class utility;

	class Polar2
	{
	public:
		Polar2();

		Polar2( const Vector2& centor = {0,0},float radius = 0.0f,float theta = 0.0f );

		Polar2( const Vector2& centor = {0,0},int radius = 0.0f,int theta = 0.0f );

		Polar2( const Vector2& vec2,const Vector2& centor = {0,0},float theta = 0.0f );

		Polar2( const Polar2& ) = default; // コピー
		Polar2( Polar2&& ) = default; // ムーブ

		// デストラクタ
		virtual ~Polar2() = default;

		Polar2& operator =( const Polar2& ) = default; // コピー
		Polar2& operator =( Polar2&& ) = default; // ムーブ

		Vector2 ToVector2();

		void RadiusIncrement( float fnum );

		void ThetaIncrement( float fnum );

		void RadiusDecrement( float fnum );

		void ThetaDecrement( float fnum );

		radius_and_phi Get();

		float GetRadius()
		{
			return radius;
		}
		float GetTheta()
		{
			return theta;
		}
		void Set( const Polar2 pol )
		{
			radius = pol.radius;
			theta = pol.theta;
		}
		void Set( const float radius,const float theta )
		{
			this->radius = radius;
			this->theta = theta;
		}
		void SetVector2( Vector2 vec )
		{
			radius = vec.Length();
			theta = std::atan( vec.y / vec.x );
		}
		void SetRadius( const float radius )
		{
			this->radius = radius;
		}
		void SetTheta( const float theta )
		{
			this->theta = theta;
		}
	private:
		const Vector2 centor;
		float radius;
		float theta;
	};
}