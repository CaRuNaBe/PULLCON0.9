#pragma once
#include"vector2.h"
namespace math
{
	// 矩形クラス
	class Rect
	{
	public:
		Rect( const Vector2& lt,const Vector2& rb )
			:leftTop{lt}
			,rightBottom{rb}
		{
		}
		Rect()
			:leftTop{0,0}
			,rightBottom{0,0}
		{
		}
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
		void Set( int left,int top,int right,int bottom )
		{
			leftTop = {static_cast<float>(left),static_cast<float>(top)};
			rightBottom = {static_cast<float>(right),static_cast<float>(bottom)};
		}
		void Set( Vector2 lefttop,Vector2 rightbottom )
		{
			leftTop = lefttop;
			rightBottom = rightbottom;
		}


		Vector2 leftTop;			// 矩形の左上
		Vector2 rightBottom;	// 矩形の右下


	};
}