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
	bool Intersect( const Sphere& a,const Sphere& b )
	{
		float x = a._vCenter.x - b._vCenter.x;
		float y = a._vCenter.y - b._vCenter.y;
		float z = a._vCenter.z - b._vCenter.z;
		float r = x * x + y * y + z * z;//‹…“¯m‚Ì‹——£‚ğ‹‚ß‚é
		float sum_radius = a._fRadius + b._fRadius;

		if ( r <= sum_radius * sum_radius )
		{
			return true;//“–‚½‚Á‚Ä‚é
		}

		return false;//ŠO‚ê‚Ä‚é

	}

	// Sphere‚Ì•`‰æ
	void Sphere::Draw( int red,int green,int blue ) const
	{
		Vector4 Center = {_vCenter.x, _vCenter.y, _vCenter.z};
		DrawSphere3D( ToDX( Center ),_fRadius,8,GetColor( red,green,blue ),GetColor( 0,0,0 ),FALSE );
	}
	// Sphere‚Ì•`‰æ
	void Sphere::DrawObject(int red, int green, int blue) const
	{
		Vector4 Center = { _vCenter.x, _vCenter.y, _vCenter.z };
		DrawSphere3D(ToDX(Center), _fRadius, 64, GetColor(red, green, blue), GetColor(0, 0, 0), FALSE);
	}

}