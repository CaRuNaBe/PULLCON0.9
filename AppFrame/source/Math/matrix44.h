#pragma once

#include <array>
#include <tuple>

namespace math
{
	class vector4;

	constexpr auto row_max = 4;
	constexpr auto column_max = 4;

	using matrix_array = std::array<std::array<float,row_max>,column_max>;

	class matrix44
	{
	public:
		// コンストラクタ
		matrix44();
		matrix44( const matrix_array values );
		matrix44( const matrix44& ) = default; // コピー
		matrix44( matrix44&& ) = default; // ムーブ

		// デストラクタ
		virtual ~matrix44() = default;

		matrix44& operator =( const matrix44& ) = default; // コピー
		matrix44& operator =( matrix44&& ) = default; // ムーブ

		const matrix44 operator *( const matrix44 rhs ) const;
		const matrix44 operator +( const vector4 rhs ) const;

		const float get_value( const int row,const int column ) const
		{
			return row_column[row][column];
		}
		const void set_value( const int row,const int column,const float value )
		{
			row_column[row][column] = value;
		}

		void zero( matrix_array& target ) const;
		void unit();

		const float determinant() const;
		const matrix44 get_inverse() const;

		void look_at( const vector4& position,const vector4& target,const vector4& up );
		void perspective( const float fov_y,const float aspect,const float near_z,const float far_z );
		void viewport( const float width,const float height );

		void transfer( const float x,const float y,const float z,bool make );
		void scale( const float x,const float y,const float z,bool make );
		void rotate_x( const float degree,bool make );
		void rotate_y( const float degree,bool make );
		void rotate_z( const float degree,bool make );

		const matrix44 get_rotate() const;

	private:
		std::tuple<float,float> get_sin_cos( const float degree ) const;

		matrix_array row_column;
	};

}
