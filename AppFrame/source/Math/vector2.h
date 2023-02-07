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
		{
		}

		constexpr Vector2( int ax,int ay ) noexcept: x{static_cast<float>(ax)},y{static_cast<float>(ay)}
		{
		}
		Vector2( const Vector2& ) = default; // コピー
		Vector2( Vector2&& ) = default; // ムーブ

		int IntX()
		{
			return static_cast<int>(x);
		}

		int IntY()
		{
			return static_cast<int>(y);
		}
		Vector2& operator =( const Vector2& ) = default; // コピー
		Vector2& operator =( Vector2&& ) = default; // ムーブ
		// ベクトルの加算 a + b ※外部関数
		const Vector2 operator+( const Vector2& rhs )const;
		// ベクトルの減算 a - b ※外部関数
		const Vector2 operator-( const Vector2& rhs )const;
		// ベクトルのスカラー倍 v * scalar ※外部関数
		const Vector2 operator*( float rhs )const;
		// ベクトルのスカラー割  v/scalar ※外部関数
		const Vector2 operator/( float rhs )const;

		// ベクトル加算代入
		Vector2& operator+=( const Vector2& right );

		// ベクトル減算代入
		Vector2& operator-=( const Vector2& right );

		// ベクトルのスカラ乗算代入
		Vector2& operator*=( float scalar );

		// ベクトル比較
		bool operator==( const Vector2& b ) const;
		bool operator!=( const Vector2& b ) const;

		// ベクトルの大きさ
		float Length() const;

		// ベクトルの正規化
		void Normalized();
		const Vector2 GetNormalize()const;

		// ベクトルの内積(Dot product) a・b
		float Dot( const Vector2& multiplicator )const;

		// ベクトルの外積(Cross product) a×b
		float Cross( const Vector2& multiplicator )const;
		// ベクトルの行列変換
		static Vector2 Transform( const Vector2& vec,const class Matrix3& mat,float w = 1.0f );
	};
}