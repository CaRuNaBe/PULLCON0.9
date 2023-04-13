#include "Polar3D.h"
namespace math
{
	Polar3D::Polar3D()
		:centor( 0,0,0 )
		,radius( 0.0f )
		,theta( 0.0f )
		,phi( 0.0f )
	{};

	Polar3D::Polar3D( const Vector4& centor,float radius,float theta,float phi )
		:centor( centor )
		,radius( radius )
		,theta( theta )
		,phi( phi )
	{};

	Polar3D::Polar3D( const Vector4& centor,int radius,int theta,int phi )
		:centor( centor )
		,radius( static_cast<float> (radius) )
		,theta( static_cast<float> (theta) )
		,phi( static_cast<float> (phi) )
	{};

	Polar3D::Polar3D( const Vector4& vec2,const Vector4& centor,float theta,float phi )
		:centor( centor )
		,radius( centor.Lenght( vec2 ) )
		,theta( static_cast<float> (theta) )
		,phi( static_cast<float> (phi) )
	{};

	Polar3D::Polar3D( const Vector4& vec )
		:centor( 0,0,0 )
		,radius( vec.Lenght() )
		,theta( std::acos( vec.GetZ() / radius ) )
		,phi( math::Sign( vec.GetY() )* std::acos( vec.GetX() / (std::sqrt( (vec.GetX() * vec.GetX()) + (vec.GetY() * vec.GetY()) )) ) )
	{};

	Vector4 Polar3D::ToVector4()
	{
		auto fnum = radius * std::sin( theta );
		return {fnum * std::cos( phi ),radius * std::cos( theta ),fnum * std::sin( phi )};
	};

	void Polar3D::RadiusIncrement( const float& radius )
	{
		this->radius += radius;
	};

	void Polar3D::RadiusDecrement( const float& radius )
	{
		this->radius -= radius;
		if ( this->radius < 0.0f )
		{
			this->radius = 0.0f;
		}
	};

	void Polar3D::ThetaIncrement( const float& theta )
	{
		this->theta += theta;
		if ( this->theta > math::utility::PI )
		{
			this->theta = math::utility::PI;
		}
	};

	void Polar3D::ThetaDecrement( const float& theta )
	{
		this->theta -= theta;
		if ( this->theta < math::utility::RADIANS_ZERO )
		{
			this->theta = math::utility::RADIANS_ZERO;
		}
	};

	void Polar3D::PhiIncrement( const float& phi )
	{
		this->phi += phi;
	};

	void Polar3D::PhiDecrement( const float& phi )
	{
		this->phi -= phi;
	};
}