//!
//! @file Collision.cpp
//!
//! @brief Õ“ËŒŸ’m
//!
#include "3dCollision.h"
#include "DxLib.h"

namespace math
{
	// AABB‚ÌŒğ·”»’è
	bool Intersect(const Sphere& a, const Sphere& b)
	{
		float x = a._vCenter.x - b._vCenter.x;
		float y = a._vCenter.y - b._vCenter.y;
		float z = a._vCenter.z - b._vCenter.z;
		float r = x * x + y * y + z * z;
		float sum_radius = a._fRadius + b._fRadius;

		if (r <= sum_radius * sum_radius)
		{
			return true;
		}
		
		return false;

	}

	// Sphere‚Ì•`‰æ
	void Sphere::Draw(int red, int green, int blue) const
	{
		vector4 Center = { _vCenter.x, _vCenter.y, _vCenter.z };
		DrawSphere3D(ToDX(Center), _fRadius, 8, GetColor(red, green, blue), GetColor(0, 0, 0), FALSE);
	}

}