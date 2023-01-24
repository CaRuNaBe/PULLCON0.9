#pragma once
#include <limits>
#include<cmath>
namespace math
{
	class matrix44;

	class vector4
	{
	public:
		/* 成分 */
		float x;
		float y;
		float z;
		float w;
		// コンストラクタ
		vector4();
		vector4( float x,float y,float z ): x( x ),y( y ),z( z ),w( 1.0 )
		{}
		vector4( float x,float y,float z,float w ): x( x ),y( y ),z( z ),w( w )
		{}
		vector4( int x,int y,int z ): x( static_cast<float>(x) ),y( static_cast<float>(y) ),z( static_cast<float>(z) ),w( 1.0 )
		{}
		vector4( int x,int y,int z,int w ): x( static_cast<float>(x) ),y( static_cast<float>(y) ),z( static_cast<float>(z) ),w( static_cast<float>(w) )
		{}
		vector4( const vector4& ) = default; // コピー
		vector4( vector4&& ) = default; // ムーブ

		// デストラクタ
		virtual ~vector4() = default;

		vector4& operator =( const vector4& ) = default; // コピー
		vector4& operator =( vector4&& ) = default; // ムーブ

		// ベクトルの加算 a + b
		const vector4 operator +( const vector4& rhs ) const;
		// ベクトルの減算 a - b
		const vector4 operator -( const vector4& rhs ) const;
		// ベクトルのスカラー倍 v * scalar
		const vector4 operator *( const float rhs ) const;
		// ベクトルのスカラー割  v/scalar
		const vector4 operator /( const float rhs ) const;
		// ベクトル加算代入
		vector4& operator+=( const vector4& right );
		// ベクトル減算代入
		vector4& operator-=( const vector4& right );
		// ベクトルのスカラ乗算代入
		vector4& operator*=( float scalar );

		// ベクトルの行列変換 オペレータ
		const vector4 operator *( const matrix44 rhs ) const;
		// ベクトルの大きさ
		const float Lenght() const;
		// ベクトルの正規化
		void Normalized();
		const vector4 GetNormalize() const;
		// ベクトルの内積(Dot product) a・b
		const float Dot( const vector4& rhs ) const;
		// ベクトルの外積(Cross product) a×b
		const vector4 Cross( const vector4& rhs ) const;
	};
} // math
