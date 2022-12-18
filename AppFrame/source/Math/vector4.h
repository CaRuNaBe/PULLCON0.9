#pragma once
#include <limits>
#include<cmath>
namespace math
{
	class matrix44;

	class vector4
	{
	public:
		/* ���� */
		float x;
		float y;
		float z;
		float w;
		// �R���X�g���N�^
		vector4();
		vector4( float x,float y,float z ): x( x ),y( y ),z( z ),w( 1.0 )
		{}
		vector4( float x,float y,float z,float w ): x( x ),y( y ),z( z ),w( w )
		{}
		vector4( int x,int y,int z ): x( static_cast<float>(x) ),y( static_cast<float>(y) ),z( static_cast<float>(z) ),w( 1.0 )
		{}
		vector4( int x,int y,int z,int w ): x( static_cast<float>(x) ),y( static_cast<float>(y) ),z( static_cast<float>(z) ),w( static_cast<float>(w) )
		{}
		vector4( const vector4& ) = default; // �R�s�[
		vector4( vector4&& ) = default; // ���[�u

		// �f�X�g���N�^
		virtual ~vector4() = default;

		vector4& operator =( const vector4& ) = default; // �R�s�[
		vector4& operator =( vector4&& ) = default; // ���[�u

		// �x�N�g���̉��Z a + b
		const vector4 operator +( const vector4& rhs ) const;
		// �x�N�g���̌��Z a - b
		const vector4 operator -( const vector4& rhs ) const;
		// �x�N�g���̃X�J���[�{ v * scalar
		const vector4 operator *( const float rhs ) const;
		// �x�N�g���̃X�J���[��  v/scalar
		const vector4 operator /( const float rhs ) const;
		// �x�N�g�����Z���
		vector4& operator+=( const vector4& right );
		// �x�N�g�����Z���
		vector4& operator-=( const vector4& right );
		// �x�N�g���̃X�J����Z���
		vector4& operator*=( float scalar );

		// �x�N�g���̍s��ϊ� �I�y���[�^
		const vector4 operator *( const matrix44 rhs ) const;
		// �x�N�g���̑傫��
		const float Lenght() const;
		// �x�N�g���̐��K��
		void Normalized();
		const vector4 GetNormalize() const;
		// �x�N�g���̓���(Dot product) a�Eb
		const float Dot( const vector4& rhs ) const;
		// �x�N�g���̊O��(Cross product) a�~b
		const vector4 Cross( const vector4& rhs ) const;
	};
} // math
