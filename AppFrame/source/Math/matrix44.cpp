#include <cmath>
#include "utility.h"
#include "matrix44.h"
#include "Vector4.h"

namespace math
{
	matrix44::matrix44()
	{
		unit();
	}

	matrix44::matrix44( const matrix_array values )
	{
		this->row_column = values;
	}

	void matrix44::zero( matrix_array& target ) const
	{
		for ( auto i = 0; i < column_max; ++i )
		{
			target[i].fill( 0.0 );
		}
	}

	void matrix44::unit()
	{
		zero( row_column );

		for ( auto i = 0; i < column_max; ++i )
		{
			row_column[i][i] = 1.0;
		}
	}

	const float matrix44::determinant() const
	{
		// 上三角行列を作成して行列式を求める
		matrix_array upper_triangular = row_column;

		for ( auto i = 0; i < column_max; ++i )
		{
			for ( auto j = 0; j < row_max; ++j )
			{
				if ( i >= j )
				{
					continue;
				}

				auto coefficient = upper_triangular[j][i] / upper_triangular[i][i];

				for ( auto k = 0; k < row_max; ++k )
				{
					upper_triangular[j][k] -= upper_triangular[i][k] * coefficient;
				}
			}
		}

		auto determinant = 1.0f;

		for ( auto i = 0; i < column_max; ++i )
		{
			determinant *= upper_triangular[i][i];
		}

		return determinant;
	}

	const matrix44 matrix44::get_inverse() const
	{
		// 掃き出し法による逆行列の計算
		matrix_array inverse{{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
		matrix_array temporary = row_column;

		for ( auto i = 0; i < column_max; ++i )
		{
			auto coefficient = 1.0f / temporary[i][i];

			for ( auto j = 0; j < row_max; ++j )
			{
				temporary[i][j] *= coefficient;
				inverse[i][j] *= coefficient;
			}

			for ( auto j = 0; j < row_max; ++j )
			{
				if ( i == j )
				{
					continue;
				}

				coefficient = temporary[j][i];

				for ( auto k = 0; k < row_max; ++k )
				{
					temporary[j][k] -= temporary[i][k] * coefficient;
					inverse[j][k] -= inverse[i][k] * coefficient;
				}
			}
		}

		return matrix44( inverse );
	}

	// 本来はカメラに属する処理だが便宜上実装する
	void matrix44::look_at( const Vector4& position,const Vector4& target,const Vector4& up )
	{
		auto axis_z = target - position;
		auto axis_x = up.Cross( axis_z );
		auto axis_y = axis_z.Cross( axis_x );

		axis_x.Normalized();
		axis_y.Normalized();
		axis_z.Normalized();

		row_column[0][0] = axis_x.x;
		row_column[0][1] = axis_y.x;
		row_column[0][2] = axis_z.x;
		row_column[0][3] = 0.0;

		row_column[1][0] = axis_x.y;
		row_column[1][1] = axis_y.y;
		row_column[1][2] = axis_z.y;
		row_column[1][3] = 0.0;

		row_column[2][0] = axis_x.z;
		row_column[2][1] = axis_y.z;
		row_column[2][2] = axis_z.z;
		row_column[2][3] = 0.0;

		row_column[3][0] = -axis_x.Dot( position );
		row_column[3][1] = -axis_y.Dot( position );
		row_column[3][2] = -axis_z.Dot( position );
		row_column[3][3] = 1.0;
	}

	void matrix44::perspective( const float fov_y,const float aspect,const float near_z,const float far_z )
	{
		auto cot = 1.0f / tan( fov_y * 0.5f );
		auto range = far_z - near_z;
		auto temp = far_z / range;

		zero( row_column );

		row_column[0][0] = cot * aspect;
		row_column[1][1] = cot;
		row_column[2][2] = temp;
		row_column[2][3] = 1.0f;
		row_column[3][2] = -near_z * temp;
	}

	void matrix44::viewport( const float width,const float height )
	{
		auto w = width * 0.5f;
		auto h = height * 0.5f;

		unit();

		row_column[0][0] = w;
		row_column[1][1] = -h;
		row_column[3][0] = w;
		row_column[3][1] = h;
	}

	const matrix44 matrix44::operator *( const matrix44 rhs ) const
	{
		matrix_array result{{{0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}}};

		for ( auto i = 0; i < column_max; ++i )
		{
			for ( auto j = 0; j < row_max; ++j )
			{
				auto m = 0.0f;

				for ( auto k = 0; k < 4; ++k )
				{
					m += row_column[i][k] * rhs.get_value( k,j );
				}

				result[i][j] = m;
			}
		}

		return matrix44( result );
	}

	const matrix44 matrix44::operator +( const Vector4 rhs ) const
	{
		matrix_array result = row_column;

		result[3][0] += rhs.x;
		result[3][1] += rhs.y;
		result[3][2] += rhs.z;

		return matrix44( result );
	}

	void matrix44::transfer( const float x,const float y,const float z,bool make )
	{
		if ( make )
		{
			unit();
		}

		row_column[3][0] += x;
		row_column[3][1] += y;
		row_column[3][2] += z;
	}

	void matrix44::scale( const float x,const float y,const float z,bool make )
	{
		if ( make )
		{
			unit();
		}

		row_column[0][0] *= x;
		row_column[1][1] *= y;
		row_column[2][2] *= z;
	}

	void matrix44::rotate_x( const float degree,bool make )
	{
		auto sin_cos = get_sin_cos( degree );
		auto sin = std::get<0>( sin_cos );
		auto cos = std::get<1>( sin_cos );

		if ( make )
		{
			unit();

			row_column[1][1] = cos;
			row_column[1][2] = sin;
			row_column[2][1] = -sin;
			row_column[2][2] = cos;
		}
		else
		{
			matrix_array array{{{1, 0, 0, 0}, {0, cos, sin, 0}, {0, -sin, cos, 0}, {0, 0, 0, 1}}};
			matrix44 rot_x( array );

			*this = *this * rot_x;
		}
	}

	void matrix44::rotate_y( const float degree,bool make )
	{
		auto sin_cos = get_sin_cos( degree );
		auto sin = std::get<0>( sin_cos );
		auto cos = std::get<1>( sin_cos );

		if ( make )
		{
			unit();

			row_column[0][0] = cos;
			row_column[0][2] = -sin;
			row_column[2][0] = sin;
			row_column[2][2] = cos;
		}
		else
		{
			matrix_array array{{{cos, 0, -sin, 0}, {0, 1, 0, 0}, {sin, 0, cos, 0}, {0, 0, 0, 1}}};
			matrix44 rot_y( array );

			*this = *this * rot_y;
		}
	}

	void matrix44::rotate_z( const float degree,bool make )
	{
		auto sin_cos = get_sin_cos( degree );
		auto sin = std::get<0>( sin_cos );
		auto cos = std::get<1>( sin_cos );

		if ( make )
		{
			unit();

			row_column[0][0] = cos;
			row_column[0][1] = sin;
			row_column[1][0] = -sin;
			row_column[1][1] = cos;
		}
		else
		{
			matrix_array array{{{cos, sin, 0, 0}, {-sin, cos, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
			matrix44 rot_z( array );

			*this = *this * rot_z;
		}
	}

	const matrix44 matrix44::get_rotate() const
	{
		matrix_array none_transfer = row_column;

		none_transfer[3][0] = 0.0;
		none_transfer[3][1] = 0.0;
		none_transfer[3][2] = 0.0;

		return matrix44( none_transfer );
	}

	std::tuple<float,float> matrix44::get_sin_cos( const float degree ) const
	{
		//auto radian = utility::degree_to_radian( degree );

		return std::make_tuple( std::sin( degree ),std::cos( degree ) );
	}

}
