#pragma once
#include<cmath>
#include <limits>
namespace math
{
	class Matrix3;
	// 2Dベクトルクラス
	class Vector2
	{
	public:
		// x成分,y成分
		float x;
		float y;

		// コンストラクタ
		Vector2() noexcept = default;

		constexpr Vector2( float ax,float ay ) noexcept: x{ax},y{ay}
		{}

		constexpr Vector2( int ax,int ay ) noexcept: x{static_cast<float>(ax)},y{static_cast<float>(ay)}
		{}

		int IntX()
		{
			return static_cast<int>(x);
		}

		int IntY()
		{
			return static_cast<int>(y);
		}

		// ベクトルの加算 a + b ※外部関数
		const Vector2 operator+( const Vector2& rhs )const
		{
			return Vector2( x + rhs.x,y + rhs.y );
		}
		// ベクトルの減算 a - b ※外部関数
		const Vector2 operator-( const Vector2& rhs )const
		{
			return Vector2( x - rhs.x,y - rhs.y );
		}
		// ベクトルのスカラー倍 v * scalar ※外部関数
		const Vector2 operator*( float rhs )const
		{
			return {x * rhs, y * rhs};
		}
		// ベクトルのスカラー割  v/scalar ※外部関数
		const Vector2 operator/( float rhs )const
		{
			return {x / rhs, y / rhs};
		}

		// ベクトル加算代入
		Vector2& operator+=( const Vector2& right )
		{
			x += right.x;
			y += right.y;
			return *this;
		}

		// ベクトル減算代入
		Vector2& operator-=( const Vector2& right )
		{
			x -= right.x;
			y -= right.y;
			return *this;
		}

		// ベクトルのスカラ乗算代入
		Vector2& operator*=( float scalar )
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		// ベクトル比較
		bool operator==( const Vector2& b ) const
		{
			if ( x == b.x && y == b.y )
			{
				return true;
			}
			return false;
		}
		bool operator!=( const Vector2& b ) const
		{
			return !(*this == b);
		}

		// ベクトルの大きさ
		float Length() const
		{
			return std::sqrt( x * x + y * y );
		}

		// ベクトルの正規化
		void Normalized()
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
		const Vector2 GetNormalize()const
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
		static float Dot( const Vector2& a,const Vector2& b )
		{
			return (a.x * b.x + a.y * b.y);
		}

		// ベクトルの外積(Cross product) a×b
		static float Cross( const Vector2& a,const Vector2& b )
		{
			return (a.x * b.y - a.y * b.x);
		}

		// ベクトルの行列変換
		static Vector2 Transform( const Vector2& vec,const class Matrix3& mat,float w = 1.0f );
	};
}