#pragma once
#include"vector2.h"
namespace math
{
	// ��`�N���X
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
		Vector2 leftTop;			// ��`�̍���
		Vector2 rightBottom;	// ��`�̉E��
	};
}