#include "appframe.h"
#include "EnemyAAA.h"
#include "Bullet.h"
#include "../ApplicationGlobal.h"

namespace
{
	constexpr int BODY = 1;
	constexpr int TURRET = 0;
	const std::string DELIMITER = ",";
	const std::string BULLET_STATE_PASS = "res/string_date/gamescript/bullet_state/";
	const std::string BULLET_STATE = "bullet_state";
	const std::string BULLET_STATEJSON = BULLET_STATE + ".json";
}
EnemyAAA::EnemyAAA( ApplicationBase& game,ModeMainGame& mode,int min_id,int max_id,int pile_num,float scale,vector4 _vPosi )
	:base( game,mode )
	,AAA_ID( utility::get_random( min_id,max_id ) )
{
	std::ostringstream filepass;

	filepass << BULLET_STATE_PASS << AAA_ID << "/" << BULLET_STATEJSON;

	auto bullet_state_date = std::make_unique<ScriptsData>();

	bullet_state_date->LoadJson( filepass.str(),BULLET_STATE );
	auto state_vector = string::Split( bullet_state_date->GetScriptLine( 0 ),DELIMITER );
	for ( auto&& state : state_vector )
	{
		int value = 0;
		string::ToInt( state,value );
		bullet_state.push_back( value );
	}

	auto pass_vector = string::Split( gGlobal.object_pass_date->GetScriptLine( AAA_ID ),DELIMITER );
	_handle_body = ResourceServer::LoadMV1Model( pass_vector[BODY] );
	_handle_turret = ResourceServer::LoadMV1Model( pass_vector[TURRET] );

	Init( pile_num,_vPosi );
	AddPieces( min_id,max_id,pile_num,scale );
}

EnemyAAA::~EnemyAAA()
{
	MV1DeleteModel( _handle_body );
	MV1DeleteModel( _handle_turret );
}

void EnemyAAA::Init( int pile_num,vector4 _vPosi )
{
	base::Init();
	_stateAAA = State::PLAY;
	_vPos = _vPosi;
	_fScale = 2.f;
	_collision._fRadius = 300.f * _fScale;
	_collisionEvent._fRadius = 500.f * _fScale;
	_collisionSearch._fRadius = _collision._fRadius * 70.f;
	_vEvent = {10000.f, 10000.f, 10000.f};
	_vDir = {0.f, 0.f, -1.f};
	_iLife = 50;

	_iType = 0;
	_iPossession = pile_num;
	_fAxialX = 0.f;
	_fAxialY = 0.f;
	_get = false;

	_CT = 30;
}

bool EnemyAAA::Update()
{
	base::Update();

	if ( _iLife < 0 )
	{
		PlaySoundMem( gGlobal._se["AAA_death"],DX_PLAYTYPE_BACK );
		Damage();
	}

	GetSearch();

	for ( auto&& obje : _mode.GetObjectServer3D().GetObjects() )
	{
		if ( obje->GetType() == Type::kPlayer
			|| obje->GetType() == Type::kEnemyAAA
			|| obje->GetType() == Type::kBullet )
		{
			if ( !_get )
			{
				break;
			}
			if ( obje->GetType() == Type::kPlayer )
			{
				if ( !_finish )
				{
					if ( _stateAAA != State::NUM )
					{
						if ( Intersect( obje->_collision,_collisionEvent ) )
						{
// イベント状態に移行させる
							_event = true;
							_stateAAA = State::EVENT;
						}
						else
						{
				// 起動状態に移行
							_stateAAA = State::PLAY;
							_coll = true;
							if ( _iType == 0 )
							{
								_vRelation = obje->_vPos;
								// 弾にバラつきを持たせる
								float randomX = static_cast<float>(utility::get_random( -700,700 ));
								float randomY = static_cast<float>(utility::get_random( 0,1000 ));
								float randomZ = static_cast<float>(utility::get_random( -700,700 ));
								_vTarget = {_vRelation.x + randomX, _vRelation.y + randomY, _vRelation.z + randomZ};
							}
						}
						// 対空砲の数を合わせる
						if ( !_pull )
						{
							_iPieces = obje->_iPieces;
						}
					}
					else
					{
						if ( obje->_pull == false )
						{
// 何個目かの対空砲か記録する
							_iPieces = obje->_iPieces + _iPart;
						}
					}
				}
				if ( obje->_finish && _pull )
				{
// 兵器化に移行
					_coll = false;
					_pull = false;
					_finish = true;
					obje->_iPieces += _iPossession;
					_stateAAA = State::WEAPON;
				}
				if ( _stateAAA == State::WEAPON )
				{
// プレイヤーと動きを同化させる
					_vPos = obje->_vPos;
					_vPos.y -= _collision._fRadius + static_cast<float>(_iPieces) * _collision._fRadius;
					_fRotatY = obje->_fRotatY + utility::PiOver2;
					_fire = obje->_fire;
					_fSpeed = obje->_fSpeed;
				}
			}
			if ( obje->GetType() == Type::kEnemyAAA )
			{
				if ( _stateAAA == State::NUM )
				{
					if ( Intersect( obje->_collision,_collision ) )
					{
						if ( _iPieces == obje->_iPieces + 1 )
						{
							if ( obje->_finish )
							{
								_finish = true;
								_iPieces = obje->_iPieces + 1;
								_stateAAA = State::WEAPON;
							}
							_iLife = obje->_iLife;
						}
					}
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

	if ( _stateAAA == State::PLAY )
	{
// イベント用コリジョンを移動
		float distance = _collision._fRadius + _collisionEvent._fRadius;
		_vEvent = {_vPos.x, _vPos.y + distance, _vPos.z};


		// 三次元極座標(r(length3D),θ(theta),φ(rad))
		float sx = _vTarget.x - _vPos.x;
		float sy = _vTarget.y - _vPos.y;
		float sz = _vTarget.z - _vPos.z;
		float length3D = sqrt( sx * sx + sy * sy + sz * sz );
		float rad = atan2( sz,sx );
		float theta = acos( sy / length3D );

		// プレイヤーを狙わない対空砲
		if ( _iType == 1 )
		{
			rad = utility::degree_to_radian( _fAxialY );
			theta = utility::degree_to_radian( _fAxialX );
			_fRotatX = theta;
		}

		// 弾の進行方向の向きを設定
		_vDir.x = cos( rad );
		_vDir.z = sin( rad );
		_vDir.y = cos( theta );
		_vDir.Normalized();

		// 一定間隔で撃つ
		if ( _CT == 0 )
		{
			float speed = 200.f;
			_fSpeed = speed;
			SeGunShotPlay();

			AddBullet( bullet_state[1],bullet_state[2],bullet_state[3],bullet_state[4],bullet_state[5],bullet_state[6] );
			_CT = 30;
		}

		if ( _iType == 0 )
		{
// 三次元極座標(r(length3D),θ(theta),φ(rad))
			sx = _vRelation.x - _vPos.x;
			sy = _vRelation.y - _vPos.y;
			sz = _vRelation.z - _vPos.z;
			length3D = sqrt( sx * sx + sy * sy + sz * sz );
			rad = atan2( sz,sx );
			theta = acos( sy / length3D );

			// モデルの向きの設定用
			_vDir.x = cos( rad );
			_vDir.z = sin( rad );
			_vDir.Normalized();
		}

		// Y軸回転
		_fRotatY = -rad;
		// X軸回転
		float rX = cos( theta );
		float degree = utility::radian_to_degree( rX );
		if ( degree >= 0.f && degree <= 40.f )
		{
			_fRotatX = rX;
		}
	}
	else if ( _stateAAA == State::WEAPON )
	{
// 対空砲によって狙う位置を下にずらす
		_vTarget.y -= static_cast<float>(_iPieces - 1) * _collision._fRadius;

		// 三次元極座標(r(length3D),θ(theta),φ(rad))
		float sx = _vTarget.x - _vPos.x;
		float sy = _vTarget.y - _vPos.y;
		float sz = _vTarget.z - _vPos.z;
		float length3D = sqrt( sx * sx + sy * sy + sz * sz );
		float rad = atan2( sz,sx );
		float theta = acos( sy / length3D );

		// 弾の進行方向の向きを設定する
		_vDir.x = cos( rad );
		_vDir.z = sin( rad );
		_vDir.y = cos( theta );
		_vDir.Normalized();

		// プレイヤーが射撃していたら一定間隔で撃つ
		if ( _fire && _CT == 0 )
		{
			float speed = 200.f;
			_fSpeed += speed;
			SeGunShotPlay();
			AddBullet( bullet_state[1],bullet_state[2],bullet_state[3],bullet_state[4],bullet_state[5],bullet_state[6] );
			_CT = 30;
		}

		// X軸回転
		float rX = cos( theta );
		float degree = utility::radian_to_degree( rX );
		if ( degree >= 0.f && degree <= 40.f )
		{
			_fRotatX = rX;
		}
	}
	else if ( _stateAAA == State::NUM )
	{
// イベント用コリジョンを移動
		float distance = _collision._fRadius + _collisionEvent._fRadius;
		_vEvent = {_vPos.x, _vPos.y + distance, _vPos.z};
		_vDir = {1.f, 0.f, 0.f};
	}

	_collision._fRadius = 300.f * _fScale;
	_collisionEvent._fRadius = 500.f * _fScale;
	_collisionSearch._fRadius = _collision._fRadius * 70.f;
	UpdateCollision();   // コリジョンアップデート

	return true;
}

void EnemyAAA::Damage()
{
	_mode.AddEffectDefeatEnemy( _vPos );
	_mode.GetObjectServer3D().Del( *this );
}

bool EnemyAAA::Draw()
{
	base::Draw();

	VECTOR pos = ToDX( _vPos );
	// モデル拡大
	MV1SetScale( _handle_body,VGet( _fScale,_fScale,_fScale ) );
	MV1SetScale( _handle_turret,VGet( _fScale,_fScale,_fScale ) );
	// モデル回転
	MV1SetRotationXYZ( _handle_body,VGet( 0.f,_fRotatY - utility::PiOver2,0.f ) );
	MV1SetRotationXYZ( _handle_turret,VGet( _fRotatX,_fRotatY - utility::PiOver2,0.f ) );
	// モデル移動
	MV1SetPosition( _handle_body,pos );
	MV1SetPosition( _handle_turret,VGet( pos.x,pos.y,pos.z ) );
	// モデル描画
	MV1DrawModel( _handle_body );
	MV1DrawModel( _handle_turret );

	// コリジョン描画
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
		else
		{
			if ( _stateAAA == State::EVENT )
			{
				vector4 color = {255, 255, 255};
				DrawCollisionSearch( color );
			}
		}
	}

	return true;
}

void EnemyAAA::GetSearch()
{
	for ( auto&& obje : _mode.GetObjectServer3D().GetObjects() )
	{
		if ( obje->GetType() == Type::kPlayer )
		{
			if ( IsSearch( *obje ) )
			{
				_get = true;
			}
			else
			{
				_get = false;
			}
		}
	}
	if ( !_get )
	{
		_coll = false;
		if ( _stateAAA != State::NUM )
		{
			_stateAAA = State::EVENT;
		}
	}
}

//void EnemyAAA::AddBullet()
//{
//	vector4 vBullet = {_vPos.x, _vPos.y + 100.f, _vPos.z};
//
//	auto bullet = std::make_shared<Bullet>( _game,_mode );
//	bullet->SetPosition( vBullet );
//	bullet->SetDir( _vDir );
//	bullet->SetSpeed( _fSpeed );
//	bullet->_fScale = 7.f;
//	bullet->_ST = 300;
//	_mode.GetObjectServer3D().Add( bullet );
//}

void EnemyAAA::AddBullet( const int& theta_split_num,const int& phi_split_num,const int& theta_degree_lower,const int& theta_degree_upper,const int& phi_degree_lower,const int& phi_degree_upper )
{
	vector4 vBullet = {_vPos.x, _vPos.y + 100.f, _vPos.z};
	_mode.AddEffectFirePlayer( vBullet );
	if ( AAA_ID == 1 )
	{
		auto bullet = std::make_shared<Bullet>( _game,_mode );
		bullet->SetPosition( vBullet );
		bullet->SetDir( _vDir );
		bullet->SetSpeed( _fSpeed );
		bullet->_fScale = 7.f;
		bullet->_ST = 300;
		_mode.GetObjectServer3D().Add( bullet );
	}
	else
	{
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

				if ( _iType == 0 )
				{
					if ( bullet_state[0] == 1 )
					{
						MATRIX to_player_dxmatrix = MGetRotVec2( Y_UP,ToDX( _vDir ) );
						VECTOR bullet_dx_dir = VTransform( ToDX( bullet_dir ),to_player_dxmatrix );

						bullet_dir = ToMath( bullet_dx_dir );
					}
					else
					{
						vector4 player_dir_xz = {_vDir.GetX(),0.0f,_vDir.GetZ()};
						MATRIX to_player_dxmatrix = MGetRotVec2( VGet( 0.0f,0.0f,-1.0f ),ToDX( player_dir_xz ) );
						VECTOR bullet_dx_dir = VTransform( ToDX( bullet_dir ),to_player_dxmatrix );

						bullet_dir = ToMath( bullet_dx_dir );
					}
				}


				bullet->SetDir( bullet_dir );
				bullet->SetSpeed( _fSpeed );
				bullet->_fScale = 7.f;
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
}



void EnemyAAA::AddPieces( int min_id,int max_id,int pile_num,float scale )
{
	for ( auto i = 0; i < pile_num; ++i )
	{
		vector4 vPiece = {_vPos.x, _vPos.y - _collision._fRadius * static_cast<float>(i + 1), _vPos.z};
		auto piece = std::make_shared<EnemyAAA>( _game,_mode,min_id,max_id,0,scale,vPiece );
		piece->_stateAAA = State::NUM;
		piece->_coll = false;
		piece->_iPart = i + 1;   // それぞれが何個目かを記憶
		_mode.GetObjectServer3D().Add( piece );
	}
}