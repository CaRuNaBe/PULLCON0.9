#pragma once
//!
//! @file Collision.h
//!
//! @brief �Փˌ��m
//!
#include "Math.h"
#include "vector4.h"
namespace math
{
	// ��
	class Sphere
	{
	public:
		void SetSphere( vector4 pos,float r )
		{
			_vCenter = pos,_fRadius = r;
		}

		vector4 _vCenter;
		float   _fRadius;
		void Draw(int red, int green, int blue) const;
		void DrawObject(int red, int green, int blue) const;
	};

	// Sphere��Sphere�̌�������
	bool Intersect( const Sphere& a,const Sphere& b );


}
