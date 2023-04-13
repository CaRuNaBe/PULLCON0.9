#pragma once
#include <DxLib.h>
struct tagVECTOR;
struct tagMATRIX;

namespace math
{
	class Vector4;
	class matrix44;
}

namespace math
{
	VECTOR ToDX( math::Vector4& vector );

	math::Vector4 ToMath( VECTOR& vector );

	MATRIX ToDX( math::matrix44& matrix );

	math::matrix44 ToMath( MATRIX& matrix );
}