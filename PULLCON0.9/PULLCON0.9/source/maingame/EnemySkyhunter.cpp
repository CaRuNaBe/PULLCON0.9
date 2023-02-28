#include  "EnemySkyhunter.h"
#include  "Bullet.h"
#include "../ApplicationGlobal.h"
namespace
{
	constexpr int SKYHUNTER_ID = 10;
}
EnemySkyhunter::EnemySkyhunter( ApplicationBase& game,ModeMainGame& mode,EnemyColumn& skyhunter )
	:base( game,mode )
	,_column( skyhunter )
{
	Init();
}

EnemySkyhunter::~EnemySkyhunter()
{}

void EnemySkyhunter::Init()
{
	base::Init();

	_handle = ResourceServer::LoadMV1Model( gGlobal.object_pass_date->GetScriptLine( SKYHUNTER_ID ) );

	_stateEnemySkyhunter = State::WAIT;

	_vPos = {0.f, 10000.f, 50000.f};
	_vEvent = _vPos;
	_fScale = 2.f;
	_fSpeed = 150.f;
	_collision._vCenter = _vPos;
	_collision._fRadius = 500.f * _fScale;
	_collisionEvent._fRadius = _collision._fRadius * 5.f * _fScale;

	_iLife = 100;

}

bool EnemySkyhunter::Update()
{
	base::Update();

	if (_stateEnemySkyhunter == State::WAIT) {
		_collision._vCenter = _vPos;
		_collisionEvent._vCenter = _vPos;
		_stateEnemySkyhunter = State::PLAY;
	}

	// 三次元極座標(r(length3D),θ(theta),φ(rad))
	float sx = 0.f,sz = 0.f,sy = 0.f;
	float length3D = 0.f;
	float rad = 0.f;
	float theta = 0.f;

	for ( auto&& obje : _mode.GetObjectServer3D().GetObjects() )
	{
		if ( obje->GetType() == Type::kPlayer
			|| obje->GetType() == Type::kBullet )
		{
			if ( obje->GetType() == Type::kPlayer )
			{
				if ( Intersect( _collisionEvent,obje->_collision ) )
				{
					_fire = true;
					_vTarget = obje->_vPos;
					// 弾にバラつきを持たせる
					float randomX = static_cast<float>(utility::get_random( -700,700 ));
					float randomY = static_cast<float>(utility::get_random( -700,1400 ));
					float randomZ = static_cast<float>(utility::get_random( -700,700 ));
					_vTarget = {_vTarget.x + randomX, _vTarget.y + randomY, _vTarget.z + randomZ};
				}
			}
			if ( obje->GetType() == Type::kBullet )
			{
				if ( IsHitObject( *obje ) )
				{
					if ( obje->_CT == 0 )
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

	// 三次元極座標
	sx = _vTarget.x - _vPos.x;
	sz = _vTarget.z - _vPos.z;
	sy = _vTarget.y - _vPos.y;
	length3D = sqrt( sx * sx + sy * sy + sz * sz );
	rad = atan2( sz,sx );
	theta = acos( sy / length3D );

	// 弾の進行方向の向きを設定
	_vDir.x = cos( rad );
	_vDir.z = sin( rad );
	_vDir.y = cos( theta );
	_vDir.Normalized();

	// 一定間隔で弾を撃つ
	if ( _fire && _CT == 0 )
	{
		AddBullet();
		_CT = 10;
	}

	if ( _column._synchronize != _synchronize )
	{
		_ST = 30 * _iPart + 1;
		_synchronize = !_synchronize;
	}
	if ( _ST == 1 )
	{
		_vVelocity = _column._vVelocity;
	}
	// 速度分移動する
	if ( _vPos.y < 6000.f && _vVelocity.y < 0.f )
	{
		_vVelocity.y = 0.f;
	}
	_vPos += _vVelocity * _fSpeed;

	if ( _iLife < 0 )
	{
		Damage();
	}

	_collision._fRadius = 500.f * _fScale;
	_collisionEvent._fRadius = _collision._fRadius * 13.f * _fScale;
	_vEvent = _vPos;
	UpdateCollision();  // コリジョン更新

	return true;
}

void EnemySkyhunter::Damage()
{
	--_column._iPieces;
	_mode.GetObjectServer3D().Del( *this );
}

bool EnemySkyhunter::Draw()
{
	base::Draw();

	// モデル拡大
	MV1SetScale( _handle,VGet( _fScale,_fScale,_fScale ) );
	// モデル回転
	MV1SetRotationYUseDir( _handle,ToDX( _vVelocity ),0.f );
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

void EnemySkyhunter::AddBullet()
{
	vector4 vBullet = {_vPos.x, _vPos.y - 500.f, _vPos.z};
	float speed = 400.f;
	auto bullet = std::make_shared<Bullet>( _game,_mode );
	bullet->SetPosition( vBullet );
	bullet->SetDir( _vDir );
	bullet->SetSpeed( speed );
	bullet->_fScale = 5.f;
	bullet->_iType = 1;
	_mode.GetObjectServer3D().Add( bullet );
}
