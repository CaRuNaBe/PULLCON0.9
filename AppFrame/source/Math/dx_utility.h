#pragma once
#include <DxLib.h>
struct tagVECTOR;
struct tagMATRIX;

namespace math
{
	class vector4;
	class matrix44;
}

namespace math
{
	VECTOR ToDX(math::vector4& vector);

	math::vector4 ToMath(VECTOR& vector);

	MATRIX ToDX(math::matrix44& matrix);

	math::matrix44 ToMath(MATRIX& matrix);
}