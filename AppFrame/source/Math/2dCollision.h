#pragma once
//!
//! @file Collision.h
//!
//! @brief 衝突検知
//!
#include "Math.h"
#include "vector2.h"
namespace math
{
	// 軸平行境界ボックス(AABB:Axis-Aligned Bounding Box）
	class AABB
	{
	public:
		Vector2 min;
		Vector2 max;
		void Draw(int red,int green,int blue) const;
	};

	// AABBとAABBの交差判定
	bool Intersect(const AABB& a,const AABB& b);

	// 線分
	class LineSegment
	{
	public:
		Vector2 start;
		Vector2 end;
		void Draw(int red,int green,int blue) const;
	};
}