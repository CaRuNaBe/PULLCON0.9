#pragma once
#include"vector2.h"
namespace math
{
	// 矩形クラス
	class Rect
	{
	public:
		Rect(const Vector2& lt,const Vector2& rb)
			:leftTop{lt}
			,rightBottom{rb}
		{}
		Vector2 GetLeftTop()
		{
			return leftTop;
		}
		Vector2 GetRightBottom()
		{
			return rightBottom;
		}
		float GetWidth()
		{
			return rightBottom.x - leftTop.x;
		}
		float GetHeight()
		{
			return rightBottom.y - leftTop.y;
		}
	private:
		Vector2 leftTop;			// 矩形の左上
		Vector2 rightBottom;	// 矩形の右下
	};
}