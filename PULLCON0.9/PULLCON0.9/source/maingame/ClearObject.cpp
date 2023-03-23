
#include "ClearObject.h"
#include "Bullet.h"
#include "../mode/ModeMainGame.h"
#include "../ApplicationGlobal.h"
namespace
{
	constexpr int GUNSHIP_ID = 12;
}
ClearObject::ClearObject( ApplicationBase& game,ModeMainGame& mode,float _radius )
	:base( game,mode )
{
	_handle = ResourceServer::LoadMV1Model(gGlobal.object_pass_date->GetScriptLine(GUNSHIP_ID));

	Init();
	radius = _radius;
}

ClearObject::~ClearObject()
{
	MV1DeleteModel( _handle );
}

void ClearObject::Init()
{
	base::Init();

	_stateClearObject = State::NUM;

	_fScale = 3.f;
	_collision._fRadius = 500.f * _fScale;
	_collisionEvent._fRadius = _collision._fRadius * 15.f;

	_iLife = 10000;

}

bool ClearObject::Update()
{
	base::Update();

	if ( _stateClearObject == State::NUM )
	{
		_vObjective = {_vPos.x ,_vPos.y, _vPos.z};
		_vPos = {_vObjective.x + radius, _vObjective.y, _vObjective.z};
		_stateClearObject = State::WAIT;
	}

	for (auto&& obje : _mode.GetObjectServer3D().GetObjects()) {
		if (obje->GetType() == Type::kPlayer
			|| obje->GetType() == Type::kBullet) {
			if (obje->GetType() == Type::kPlayer) {
				if (Intersect(_collisionEvent, obje->_collision)) {
					_fire = true;
					_vRelation = obje->_vPos;
					// 弾にバラつきを持たせる
					float randomX = static_cast<float>(utility::get_random( -700,700 ));
					float randomY = static_cast<float>(utility::get_random( -700,1400 ));
					float randomZ = static_cast<float>(utility::get_random( -700,700 ));
					_vTarget = {_vRelation.x + randomX, _vRelation.y + randomY, _vRelation.z + randomZ};
				}
				else
				{
				}
			}
			if ( obje->GetType() == Type::kBullet )
			{
				if ( IsHitObject( *obje ) )
				{
					if (obje->_iType == 2)
					{
						_CT = 10;
						_overlap = true;
						obje->Damage();
						_iLife -= obje->_iDamage;
					}
				}
			}
		}
	}

	// 三次元極座標(r(length3D),θ(theta),φ(rad))
	float sx = _vTarget.x - _vPos.x;
	float sz = _vTarget.z - _vPos.z;
	float sy = _vTarget.y - _vPos.y;
	float length3D = sqrt( sx * sx + sy * sy + sz * sz );
	float rad = atan2( sz,sx );
	float theta = acos( sy / length3D );

	// 弾の進行方向の向きを設定
	_vDir.x = cos( rad );
	_vDir.z = sin( rad );
	_vDir.y = cos( theta );
	_vDir.Normalized();

	vector4 effectPos = _vPos + _vDir * _collision._fRadius;
	// 一定間隔で撃つ
	if ( _fire && _CT == 0 )
	{
		AddBullet();
		_mode.AddEffectFireGunship(effectPos);
		SeGunShotPlay();
		_CT = 5;
	}

	// 極座標(r(length3D),θ(rad))
	sx = _vPos.x - _vObjective.x;
	sz = _vPos.z - _vObjective.z;
	length3D = sqrt( sx * sx + sz * sz );
	rad = atan2( sz,sx );
	// 角速度
	rad += utility::TwoPi / (12.f * 60.f);

	_vPos.x = _vObjective.x + cos( rad ) * length3D;
	_vPos.z = _vObjective.z + sin( rad ) * length3D;

	// フォワードベクトル
	_vDir.x = cos( rad );
	_vDir.z = sin( rad );
	_vDir.Normalized();


	if ( _iLife < 0 )
	{
		Damage();
	}

	_collision._fRadius = 500.f * _fScale;
	_collisionEvent._fRadius = _collision._fRadius * 15.f;
	_vEvent = _vPos;
	UpdateCollision();  // コリジョン更新

	return true;
}

void ClearObject::Damage()
{
	PlaySoundMem( gGlobal._se["gunship_death"],DX_PLAYTYPE_BACK );
	_mode.AddEffectDeathObject( _vPos );
	_mode.GetObjectServer3D().Del( *this );
}

bool ClearObject::Draw()
{
	base::Draw();

	// モデル拡大
	MV1SetScale( _handle,VGet( _fScale,_fScale,_fScale ) );
	// モデル回転
	MV1SetRotationYUseDir( _handle,ToDX( _vDir ),0.f );
	// モデル移動
	MV1SetPosition( _handle,ToDX( _vPos ) );
	// モデル描画
	MV1DrawModel( _handle );

	// コリジョン描画
	vector4 color = {255,255,255};
	if ( !((ModeMainGame&)_mode)._dbgCollisionDraw )
	{
		DrawCollision( color );
		DrawCollisionEvent( color );
		if ( _overlap )
		{
			color = {255, 0, 0};
			DrawCollision( color );
		}
	}
	return true;
}

void ClearObject::AddBullet()
{
	vector4 vBullet = {_vPos.x, _vPos.y - 500.f, _vPos.z};
	auto bullet = std::make_shared<Bullet>( _game,_mode );
	bullet->SetPosition( vBullet );
	bullet->SetDir( _vDir );
	bullet->SetSpeed(bullet->_fSpeed * 4.f);
	bullet->_iDamage = 500;
	bullet->_iType = 1;
	_mode.GetObjectServer3D().Add( bullet );
}