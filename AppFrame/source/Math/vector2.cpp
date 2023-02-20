#include "Vector2.h"
#include "matrix33.h"
namespace math
{
	// ベクトルの加算 a + b ※外部関数
	const Vector2 Vector2::operator+( const Vector2& rhs )const
	{
		return Vector2( x + rhs.x,y + rhs.y );
	}
	// ベクトルの減算 a - b ※外部関数
	const Vector2 Vector2::operator-( const Vector2& rhs )const
	{
		return Vector2( x - rhs.x,y - rhs.y );
	}
	// ベクトルのスカラー倍 v * scalar ※外部関数
	const Vector2 Vector2::operator*( float rhs )const
	{
		return {x * rhs, y * rhs};
	}
	// ベクトルのスカラー割  v/scalar ※外部関数
	const Vector2 Vector2::operator/( float rhs )const
	{
		return {x / rhs, y / rhs};
	}

	// ベクトル加算代入
	Vector2& Vector2::operator+=( const Vector2& right )
	{
		x += right.x;
		y += right.y;
		return *this;
	}

	// ベクトル減算代入
	Vector2& Vector2::operator-=( const Vector2& right )
	{
		x -= right.x;
		y -= right.y;
		return *this;
	}

	// ベクトルのスカラ乗算代入
	Vector2& Vector2::operator*=( float scalar )
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	// ベクトル比較
	bool Vector2::operator==( const Vector2& b ) const
	{
		if ( x == b.x && y == b.y )
		{
			return true;
		}
		return false;
	}
	bool Vector2::operator!=( const Vector2& b ) const
	{
		return !(*this == b);
	}

	// ベクトルの大きさ
	float Vector2::Length( const Vector2& backvec ) const
	{
		Vector2 vec = {x - backvec.x,y - backvec.y};
		return std::sqrt( vec.x * vec.x + vec.y * vec.y );
	}

	// ベクトルの正規化
	void Vector2::Normalized()
	{
		auto length = Length();

		// 誤差未満ならゼロとみなす。
		if ( std::abs( length ) < std::numeric_limits<float>::epsilon() )
		{
			x = 0.0;
			y = 0.0;
		}
		else
		{
			x /= length;
			y /= length;
		}
	}
	const Vector2 Vector2::GetNormalize()const
	{
		auto len = Length();
		auto nx = 0.0f;
		auto ny = 0.0f;
		// 誤差未満ならゼロとみなす。
		if ( std::abs( len ) < std::numeric_limits<float>::epsilon() )
		{
			nx = 0.0f;
			ny = 0.0f;
		}
		else
		{
			nx = x / len;
			ny = y / len;
		}
		return Vector2( nx,ny );
	}

	// ベクトルの内積(Dot product) a・b
	float Vector2::Dot( const Vector2& multiplicator )const
	{
		return (x * multiplicator.x + y * multiplicator.y);
	}

	// ベクトルの外積(Cross product) a×b
	float Vector2::Cross( const Vector2& multiplicator )const
	{
		return (x * multiplicator.y - y * multiplicator.x);
	}

	// ベクトルの行列変換
	Vector2 Vector2::Transform( const Vector2& vec,const Matrix3& mat,float w )
	{
		return {
			vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + w * mat.m[2][0],
			vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + w * mat.m[2][1],
		};
	}

	Vector2 Vector2::GetCentor( const Vector2& right )
	{
		float x2 = ((x * 2.0f) + right.x) / 2.0f;
		float y2 = ((y * 2.0f) + right.y) / 2.0f;
		Vector2 vec = {x2,y2};
		return vec;
	};
}