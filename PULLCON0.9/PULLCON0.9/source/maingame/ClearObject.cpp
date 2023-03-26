
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
	_handle = ResourceServer::LoadMV1Model( gGlobal.object_pass_date->GetScriptLine( GUNSHIP_ID ) );

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

	_iLife = 100;

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
					if ( obje->_iType == 2 )
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
		_mode.AddEffectFireGunship( effectPos );
		SeGunShotPlay();
		_CT = 60;
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
	const int theta_split_num = 60;
	const int phi_split_num = 30;
	const int theta_degree_lower = 0;
	const int theta_degree_upper = 30;
	const int phi_degree_lower = 0;
	const int phi_degree_upper = 361;

	vector4 vBullet = {_vPos.x, _vPos.y - 500.f, _vPos.z};
	Polar3D bullet_dir_pol = {{0,0,0},1.0f,0.0f,0.0f};
	const auto THETA_ADD_NUM = math::utility::PI / theta_split_num;
	const auto PHI_ADD_NUM = math::utility::TwoPi / phi_split_num;
	const auto THETA_RADIAN_LOWER = utility::degree_to_radian( static_cast<float>(theta_degree_lower) );
	const auto THETA_RADIAN_UPPER = utility::degree_to_radian( static_cast<float>(theta_degree_upper) );
	const auto PHI_RADIAN_LOWER = utility::degree_to_radian( static_cast<float>(phi_degree_lower) );
	const auto PHI_RADIAN_UPPER = utility::degree_to_radian( static_cast<float>(phi_degree_upper) );

	const auto Y_UP = VGet( 0.f,1.f,0.f );
	for ( int i = 0; i < theta_split_num; i++ )
	{
		for ( int i = 0; i < phi_split_num; i++ )
		{
			auto bullet = std::make_shared<Bullet>( _game,_mode );
			bullet->SetPosition( vBullet );

			auto bullet_dir = bullet_dir_pol.ToVector4();

			MATRIX to_player_dxmatrix = MGetRotVec2( Y_UP,ToDX( _vDir ) );
			VECTOR bullet_dx_dir = VTransform( ToDX( bullet_dir ),to_player_dxmatrix );

			bullet_dir = ToMath( bullet_dx_dir );


			bullet->SetDir(bullet_dir);
			bullet->_iType = _iType;
			bullet->_ST = 300;
			bullet_dir_pol.PhiIncrement( PHI_ADD_NUM );


			if ( bullet_dir_pol.GetTheta() < THETA_RADIAN_LOWER ||
				bullet_dir_pol.GetTheta() >= THETA_RADIAN_UPPER ||
				bullet_dir_pol.GetPhi() < PHI_RADIAN_LOWER ||
				bullet_dir_pol.GetPhi() >= PHI_RADIAN_UPPER )
			{
				continue;
			}
			_mode.GetObjectServer3D().Add( bullet );

		}
		bullet_dir_pol.SetPhi( 0.0f );

		bullet_dir_pol.ThetaIncrement( THETA_ADD_NUM );
	}
}