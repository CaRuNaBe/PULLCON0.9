#include "appframe.h"
#include "EnemyAAA.h"
#include "Bullet.h"
#include "../mode/ModeMainGame.h"

EnemyAAA::EnemyAAA( ApplicationBase& game,ModeBase& mode,int min_id,int max_id,int pile_num )
	:base( game,mode )
{

	_handle_body = MV1LoadModel( "res/enemy/AAA/canon_mk1/mvi/cg_Canon_Mk1_dodai.mv1" );
	_handle_turret = MV1LoadModel( "res/enemy/AAA/canon_mk1/mvi/cg_Canon_Mk1_houtou.mv1" );

	Init();
}

EnemyAAA::~EnemyAAA()
{

}

void EnemyAAA::Init()
{
	base::Init();
	_stateAAA = State::PLAY;

	_collision._fRadius = 300.f;
	_collisionEvent._fRadius = 500.f;

	//_vPos = { 0.f, 50.f, 0.f };
	_vRelation = {0.f, 0.f, 0.f};
	_vEvent = {1000.f, 1000.f, 1000.f};


	_CT = 30;
}

bool EnemyAAA::Update()
{
	base::Update();

	for ( auto&& obje : _mode.GetObjectServer3D().GetObjects() )
	{
		if ( obje->GetType() == Type::kPlayer
				 || obje->GetType() == Type::kBullet )
		{
			if ( obje->GetType() == Type::kPlayer )
			{
				if ( !_finish )
				{
					if ( Intersect( obje->_collision,_collisionEvent ) )
					{
						_event = true;
						_stateAAA = State::EVENT;
					}
					else
					{
						_stateAAA = State::PLAY;
						_vTarget = obje->_vPos;
					}
				}
				if ( obje->_finish && _pull )
				{
					_coll = false;
					_pull = false;
					_finish = true;
					_stateAAA = State::WEAPON;
				}
				if ( _stateAAA == State::WEAPON )
				{
					_vPos = obje->_vPos;
					_vPos.y -= _collision._fRadius * 2.f;
					_fRotatY = obje->_fRotatY + utility::PiOver2;
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
					}
				}
			}
		}
	}

	if ( _stateAAA == State::PLAY )
	{
		float distance = _collision._fRadius + _collisionEvent._fRadius;
		_vEvent = {_vPos.x, _vPos.y + distance, _vPos.z};

		// 三次元極座標(r(length3D),θ(theta),φ(rad))
		float sx = _vTarget.x - _vPos.x;
		float sy = 300.f + _vTarget.y - _vPos.y;   // 少し上を狙う
		float sz = _vTarget.z - _vPos.z;
		float length3D = sqrt( sx * sx + sy * sy + sz * sz );
		float rad = atan2( sz,sx );
		float theta = acos( sy / length3D );

		_vDir.x = cos( rad );
		_vDir.z = sin( rad );
		_vDir.y = cos( theta );
		_vDir.Normalized();

		if ( _CT == 0 )
		{
			AddBullet();
			_CT = 10;
		}

		_fRotatY = -rad;
		float rX = cos( theta );
		float degree = utility::radian_to_degree( rX );
		if ( degree >= 0.f && degree <= 40.f )
		{
			_fRotatX = rX;
		}
	}
	else if ( _stateAAA == State::WEAPON )
	{
// 三次元極座標(r(length3D),θ(theta),φ(rad))
		float sx = _vTarget.x - _vPos.x;
		float sy = _vTarget.y - _vPos.y;
		float sz = _vTarget.z - _vPos.z;
		float length3D = sqrt( sx * sx + sy * sy + sz * sz );
		float rad = atan2( sz,sx );
		float theta = acos( sy / length3D );

		_vDir.x = cos( rad );
		_vDir.z = sin( rad );
		_vDir.y = cos( theta );
		_vDir.Normalized();

		if ( _CT == 0 )
		{
			AddBullet();
			_CT = 10;
		}

		float rX = cos( theta );
		float degree = utility::radian_to_degree( rX );
		if ( degree >= 0.f && degree <= 40.f )
		{
			_fRotatX = rX;
		}
	}

	UpdateCollision();

	return true;
}

void EnemyAAA::Damage()
{
	_mode.GetObjectServer3D().Del( *this );
}

bool EnemyAAA::Draw()
{
	base::Draw();

	VECTOR pos = ToDX( _vPos );
	MV1SetRotationXYZ( _handle_body,VGet( 0.f,_fRotatY,0.f ) );
	MV1SetRotationZYAxis( _handle_turret,VGet( -(_vDir.z),0.f,_vDir.x ),VGet( 0.f,1.f,0.f ),_fRotatX );
	MV1SetPosition( _handle_body,pos );
	MV1SetPosition( _handle_turret,VGet( pos.x,pos.y + 40.f,pos.z ) );
	MV1DrawModel( _handle_body );
	MV1DrawModel( _handle_turret );

	if ( !((ModeMainGame&)_mode)._dbgCollisionDraw )
	{
		if ( _coll )
		{
			vector4 color = {255, 255, 255};
			DrawCollision( color );
			if ( !_finish )
			{
				DrawCollisionEvent( color );
			}
			if ( _overlap )
			{
				color = {255, 0, 0};
				DrawCollision( color );
			}
			if ( _event )
			{
				color = {0, 255, 0};
				DrawCollisionEvent( color );
			}
		}
	}

	return true;
}

void EnemyAAA::AddBullet()
{
	vector4 vBullet = {_vPos.x, _vPos.y + 100.f, _vPos.z};
	auto bullet = std::make_shared<Bullet>( _game,_mode );
	bullet->SetPosition( vBullet );
	bullet->SetDir( _vDir );
	_mode.GetObjectServer3D().Add( bullet );
}