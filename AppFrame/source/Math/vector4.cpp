#include <cmath>
#include "Vector4.h"
#include "matrix44.h"

namespace math
{
	Vector4::Vector4()
	{
		x = 0.0; y = 0.0; z = 0.0; w = 1.0;
	}

	const float Vector4::Lenght( const Vector4& second ) const
	{
		return sqrt( (x - second.GetX()) * (x - second.GetX()) + (y - second.GetY()) * (y - second.GetY()) + (z - second.GetZ()) * (z - second.GetZ()) );
	}

	//正規化
	void Vector4::Normalized()
	{
		auto len = Lenght();
		// 誤差未満ならゼロとみなす。
		if ( std::abs( len ) < std::numeric_limits<float>::epsilon() )
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
		else
		{
			x /= len;
			y /= len;
			z /= len;
		}
	}
	const Vector4 Vector4::GetNormalize() const
	{
		auto len = Lenght();
		auto nx = 0.0f;
		auto ny = 0.0f;
		auto nz = 0.0f;
		// 誤差未満ならゼロとみなす。
		if ( std::abs( len ) < std::numeric_limits<float>::epsilon() )
		{
			nx = 0.0f;
			ny = 0.0f;
			nz = 0.0f;
		}
		else
		{
			nx = x / len;
			ny = y / len;
			nz = z / len;
		}
		return Vector4( nx,ny,nz );
	}

	const float Vector4::Dot( const Vector4& rhs ) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	const Vector4 Vector4::Cross( const Vector4& rhs ) const
	{
		auto cx = y * rhs.z - z * rhs.y;
		auto cy = z * rhs.x - x * rhs.z;
		auto cz = x * rhs.y - y * rhs.x;

		return Vector4( cx,cy,cz );
	}

	const Vector4 Vector4::operator+( const Vector4& rhs ) const
	{
		return Vector4( x + rhs.x,y + rhs.y,z + rhs.z );
	}

	const Vector4 Vector4::operator-( const Vector4& rhs ) const
	{
		return Vector4( x - rhs.x,y - rhs.y,z - rhs.z );
	}

	const Vector4 Vector4::operator*( const Vector4& rhs ) const
	{
		return Vector4( x * rhs.x,y * rhs.y,z * rhs.z );
	}
	
	const Vector4 Vector4::operator*( const float rhs ) const
	{
		return Vector4( x * rhs,y * rhs,z * rhs );
	}

	const Vector4 Vector4::operator/( const float rhs ) const
	{
		return Vector4( x / rhs,y / rhs,z / rhs );
	}
	// ベクトル加算代入
	Vector4& Vector4::operator+=( const Vector4& right )
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this;
	};
	// ベクトル減算代入
	Vector4& Vector4::operator-=( const Vector4& right )
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}
	// ベクトルのスカラ乗算代入
	Vector4& Vector4::operator*=( float scalar )
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	const Vector4 Vector4::operator *( const matrix44 rhs ) const
	{
		auto mx = x * rhs.get_value( 0,0 )
			+ y * rhs.get_value( 1,0 )
			+ z * rhs.get_value( 2,0 )
			+ rhs.get_value( 3,0 );

		auto my = x * rhs.get_value( 0,1 )
			+ y * rhs.get_value( 1,1 )
			+ z * rhs.get_value( 2,1 )
			+ rhs.get_value( 3,1 );

		auto mz = x * rhs.get_value( 0,2 )
			+ y * rhs.get_value( 1,2 )
			+ z * rhs.get_value( 2,2 )
			+ rhs.get_value( 3,2 );

		auto mw = x * rhs.get_value( 0,3 )
			+ y * rhs.get_value( 1,3 )
			+ z * rhs.get_value( 2,3 )
			+ rhs.get_value( 3,3 );

		return Vector4( mx,my,mz,mw );
	}

} // math
