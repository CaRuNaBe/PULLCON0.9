#pragma once
#include <limits>
#include<cmath>
namespace math
{
	class matrix44;

	class Vector4
	{
	public:
		/* 成分 */
		float x;
		float y;
		float z;
		float w;
		// コンストラクタ
		Vector4();
		Vector4( float x,float y,float z ): x( x ),y( y ),z( z ),w( 1.0 )
		{}
		Vector4( float x,float y,float z,float w ): x( x ),y( y ),z( z ),w( w )
		{}
		Vector4( int x,int y,int z ): x( static_cast<float>(x) ),y( static_cast<float>(y) ),z( static_cast<float>(z) ),w( 1.0 )
		{}
		Vector4( int x,int y,int z,int w ): x( static_cast<float>(x) ),y( static_cast<float>(y) ),z( static_cast<float>(z) ),w( static_cast<float>(w) )
		{}
		Vector4( const Vector4& ) = default; // コピー
		Vector4(Vector4&& ) = default; // ムーブ

		// デストラクタ
		virtual ~Vector4() = default;

		Vector4& operator =( const Vector4& ) = default; // コピー
		Vector4& operator =(Vector4&& ) = default; // ムーブ

		// ベクトルの加算 a + b
		const Vector4 operator +( const Vector4& rhs ) const;
		// ベクトルの減算 a - b
		const Vector4 operator -( const Vector4& rhs ) const;
		// ベクトルのかけ算 v * v
		const Vector4 operator *( const Vector4& rhs ) const;
		// ベクトルのスカラー倍 v * scalar
		const Vector4 operator *( const float rhs ) const;
		// ベクトルのスカラー割  v/scalar
		const Vector4 operator /( const float rhs ) const;
		// ベクトル加算代入
		Vector4& operator+=( const Vector4& right );
		// ベクトル減算代入
		Vector4& operator-=( const Vector4& right );
		// ベクトルのスカラ乗算代入
		Vector4& operator*=( float scalar );

		// ベクトルの行列変換 オペレータ
		const Vector4 operator *( const matrix44 rhs ) const;
		// ベクトルの大きさ
		const float Lenght( const Vector4& second = {0,0,0} ) const;
		// ベクトルの正規化
		void Normalized();
		const Vector4 GetNormalize() const;
		// ベクトルの内積(Dot product) a・b
		const float Dot( const Vector4& rhs ) const;
		// ベクトルの外積(Cross product) a×b
		const Vector4 Cross( const Vector4& rhs ) const;

		const float GetX()const
		{
			return x;
		}
		const float GetY()const
		{
			return y;
		}
		const float GetZ()const
		{
			return z;
		}
		const float GetW()const
		{
			return w;
		}

		void SetX( const float& x )
		{
			this->x = x;
		}
		const float SetY( const float& y )
		{
			this->y = y;
		}
		const float SetZ( const float& z )
		{
			this->z = z;
		}
		const float SetW( const float& w )
		{
			this->w = w;
		}
	};
} // math
