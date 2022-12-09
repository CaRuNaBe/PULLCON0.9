#include "dx_utility.h"
#include "vector4.h"
#include "matrix44.h"
#include <utility>

namespace math
{
	VECTOR ToDX(math::vector4& vector)
	{
		return VGet(static_cast<float>(vector.get_x()),static_cast<float>(vector.get_y()),static_cast<float>(vector.get_z()));
	}

	math::vector4 ToMath(VECTOR& vector)
	{
		return math::vector4(static_cast<float>(vector.x),static_cast<float>(vector.y),static_cast<float>(vector.z));
	}

	MATRIX ToDX(math::matrix44& matrix)
	{
		MATRIX ret;

		for(auto i = 0; i < math::row_max; ++i)
		{
			for(auto j = 0; j < math::column_max; ++j)
			{
				ret.m[i][j] = static_cast<float>(matrix.get_value(i,j));
			}
		}

		return ret;
	}

	math::matrix44 ToMath(MATRIX& matrix)
	{
		math::matrix44 ret;

		for(auto i = 0; i < math::row_max; ++i)
		{
			for(auto j = 0; j < math::column_max; ++j)
			{
				ret.set_value(i,j,static_cast<float>(matrix.m[i][j]));
			}
		}

		return ret;
	}

	/*
	namespace MyLib
	{
		inline void DrawModiGraph(
			float x1,float y1,
			float x2,float y2,
			float x3,float y3,
			float x4,float y4,
			int grHandle,bool transFlag)
		{
			DxLib::DrawModiGraph(
				static_cast< int >(x1),static_cast< int >(y1),
				static_cast< int >(x2),static_cast< int >(y2),
				static_cast< int >(x3),static_cast< int >(y3),
				static_cast< int >(x4),static_cast< int >(y4),grHandle,transFlag);
		}

		inline void DrawModiGraph(Vector2& lt,Vector2& rt,Vector2& rb,Vector2& lb,int grHandle,bool transFlag)
		{
			DxLib::DrawModiGraph(
				static_cast< int >(lt.x),static_cast< int >(lt.y),
				static_cast< int >(rt.x),static_cast< int >(rt.y),
				static_cast< int >(rb.x),static_cast< int >(rb.y),
				static_cast< int >(lb.x),static_cast< int >(lb.y),grHandle,transFlag);
		}

		// ��]�g�k���s�ړ��s����g���ĕ`�悷��
		inline void DrawModiGraph(const Matrix3& view,const Vector2& position,const Vector2& scale,double angle,int width,int height,int rgHandle)
		{
			// ��]�~�g�k�~���s�ړ�
			Matrix3 m = Matrix3::CreateRotation(angle);
			m *= Matrix3::CreateScale(scale);
			m *= Matrix3::CreateTranslation(position);

			m *= view;

			// �`�悷��摜��4�̒��_���W
			std::array<Vector2,4> pos = {
				Vector2{-width / 2.0, -height / 2.0 },	// ���ォ��E���
				Vector2{ width / 2.0, -height / 2.0 },	// �E��
				Vector2{ width / 2.0,  height / 2.0 },	// �E��
				Vector2{-width / 2.0,  height / 2.0 }		// ����
				// ���]�p
				//Vector2{ width / 2.0, -height / 2.0 },	// �E�ォ�獶���
				//Vector2{-width / 2.0, -height / 2.0 },	// ����
				//Vector2{-width / 2.0,  height / 2.0 },	// ����
				//Vector2{ width / 2.0,  height / 2.0 }		// �E��
			};
			// 4�̒��_���W�S�Ăɍs����|���ĕϊ�����
			for(auto&& v : pos)
			{
				v = Vector2::Transform(v,m);
			}
			// �ϊ��������W�ŕ`�悷��
			MyLib::DrawModiGraph(pos[0],pos[1],pos[2],pos[3],rgHandle,true);
		}

		inline void DrawModiGraph(const Matrix3& view,const Vector2& position,double zoom,double angle,int width,int height,int rgHandle)
		{
			MyLib::DrawModiGraph(view,position,{zoom, zoom},angle,width,height,rgHandle);
		}
	};
	*/
}