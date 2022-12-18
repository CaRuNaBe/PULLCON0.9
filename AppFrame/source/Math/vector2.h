#pragma once
#include<cmath>
#include <limits>
namespace math
{
	class Matrix3;
	// 2D�x�N�g���N���X
	class Vector2
	{
	public:
		// x����,y����
		float x;
		float y;

		// �R���X�g���N�^
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

		// �x�N�g���̉��Z a + b ���O���֐�
		const Vector2 operator+( const Vector2& rhs )const
		{
			return Vector2( x + rhs.x,y + rhs.y );
		}
		// �x�N�g���̌��Z a - b ���O���֐�
		const Vector2 operator-( const Vector2& rhs )const
		{
			return Vector2( x - rhs.x,y - rhs.y );
		}
		// �x�N�g���̃X�J���[�{ v * scalar ���O���֐�
		const Vector2 operator*( float rhs )const
		{
			return {x * rhs, y * rhs};
		}
		// �x�N�g���̃X�J���[��  v/scalar ���O���֐�
		const Vector2 operator/( float rhs )const
		{
			return {x / rhs, y / rhs};
		}

		// �x�N�g�����Z���
		Vector2& operator+=( const Vector2& right )
		{
			x += right.x;
			y += right.y;
			return *this;
		}

		// �x�N�g�����Z���
		Vector2& operator-=( const Vector2& right )
		{
			x -= right.x;
			y -= right.y;
			return *this;
		}

		// �x�N�g���̃X�J����Z���
		Vector2& operator*=( float scalar )
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		// �x�N�g����r
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

		// �x�N�g���̑傫��
		float Length() const
		{
			return std::sqrt( x * x + y * y );
		}

		// �x�N�g���̐��K��
		void Normalized()
		{
			auto length = Length();

			// �덷�����Ȃ�[���Ƃ݂Ȃ��B
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
			// �덷�����Ȃ�[���Ƃ݂Ȃ��B
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

		// �x�N�g���̓���(Dot product) a�Eb
		static float Dot( const Vector2& a,const Vector2& b )
		{
			return (a.x * b.x + a.y * b.y);
		}

		// �x�N�g���̊O��(Cross product) a�~b
		static float Cross( const Vector2& a,const Vector2& b )
		{
			return (a.x * b.y - a.y * b.x);
		}

		// �x�N�g���̍s��ϊ�
		static Vector2 Transform( const Vector2& vec,const class Matrix3& mat,float w = 1.0f );
	};
}