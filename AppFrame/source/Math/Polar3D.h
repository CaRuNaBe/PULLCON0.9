/*****************************************************************//**
 * @file   Polar3D.h
 * @brief  三次元極座標定義
 *
 * @author 阿部健太郎
 * @date   March 2023
 *********************************************************************/
#pragma once
#include "vector4.h"
#include "utility.h"
namespace math
{
	class Polar3D
	{
	public:
		Polar3D();

		Polar3D( const vector4& centor = {0,0,0},float radius = 0.0f,float theta = 0.0f,float phi = 0.0f );

		Polar3D( const vector4& centor = {0,0,0},int radius = 0.0f,int theta = 0.0f,int phi = 0.0f );

		Polar3D( const vector4& vec2,const vector4& centor = {0,0,0},float theta = 0.0f,float phi = 0.0f );

		Polar3D( const Polar3D& ) = default; // コピー
		Polar3D( Polar3D&& ) = default; // ムーブ

		// デストラクタ
		virtual ~Polar3D() = default;

		Polar3D& operator =( const Polar3D& ) = default; // コピー
		Polar3D& operator =( Polar3D&& ) = default; // ムーブ

		vector4 ToVector4();

		void RadiusIncrement( const float& radius );

		void RadiusDecrement( const float& radius );

		void ThetaIncrement( const float& theta );

		void ThetaDecrement( const float& theta );

		void PhiIncrement( const float& phi );

		void PhiDecrement( const float& phi );


		void SetRadius( const float& radius )
		{
			this->radius = radius;
		}
		void SetTheta( const float& theta )
		{
			this->theta = theta;
		}
		void SetPhi( const float& phi )
		{
			this->phi = phi;
		}
		void Set( const Polar3D& pol )
		{
			radius = pol.GetRadius();
			theta = pol.GetTheta();
			phi = pol.GetPhi();
		}
		void Set( const float& radius,const float& theta,const float& phi )
		{
			this->radius = radius;
			this->theta = theta;
			this->phi = phi;
		}
		float GetRadius()const
		{
			return radius;
		}
		float GetTheta()const
		{
			return theta;
		}
		float GetPhi()const
		{
			return phi;
		}
	private:
		/** 中心点 直交座標に戻すとき必要 */
		const vector4 centor;
		float radius;
		float theta;
		float phi;
	};
}
