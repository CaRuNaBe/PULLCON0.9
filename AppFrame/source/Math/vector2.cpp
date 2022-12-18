#include "vector2.h"
#include "matrix33.h"
namespace math
{
	// ベクトルの行列変換
	Vector2 Vector2::Transform(const Vector2& vec,const Matrix3& mat,float w)
	{
		return {
			vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + w * mat.m[2][0],
			vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + w * mat.m[2][1],
		};
	}
}