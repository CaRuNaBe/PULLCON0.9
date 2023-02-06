#include "appframe.h"
#include "EnemyAAA.h"
#include "Bullet.h"
#include "../mode/ModeMainGame.h"

EnemyAAA::EnemyAAA( ApplicationBase& game,ModeBase& mode,int min_id,int max_id,int pile_num,vector4 _vPosi )
	:base( game,mode )
{

	_handle_body = MV1LoadModel( "res/enemy/AAA/canon_mk1/mvi/cg_Canon_Mk1_dodai.mv1" );
	_handle_turret = MV1LoadModel( "res/enemy/AAA/canon_mk1/mvi/cg_Canon_Mk1_houtou.mv1" );

	Init(pile_num, _vPosi);
	AddPieces(pile_num);
}

EnemyAAA::~EnemyAAA()
{

}

void EnemyAAA::Init(int pile_num, vector4 _vPosi)
{
	base::Init();
	_stateAAA = State::PLAY;
	_vPos = _vPosi;
	_fScale = 2.f;
	_collision._fRadius = 300.f * _fScale;
	_collisionEvent._fRadius = 500.f * _fScale;
	_collisionSearch._fRadius = _collision._fRadius * 70.f;
	_vEvent = { 10000.f, 10000.f, 10000.f };
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

	if (_iLife < 0) {
		//_mode.GetObjectServer3D().Del(*this);
	}

	GetSearch();

	for (auto&& obje : _mode.GetObjectServer3D().GetObjects()) {
		if (obje->GetType() == Type::kPlayer
		 || obje->GetType() == Type::kEnemyAAA
		 || obje->GetType() == Type::kBullet) {
			if (!_get) { break; }
			if (obje->GetType() == Type::kPlayer) {
				if(!_finish){
					if (_stateAAA != State::NUM) {
						if (Intersect(obje->_collision, _collisionEvent)) {
							// イベント状態に移行させる
							_event = true;
							_stateAAA = State::EVENT;
						}
						else {
							// 起動状態に移行
							_stateAAA = State::PLAY;
							_coll = true;
							if (_iType == 0) {
								_vRelation = obje->_vPos;
								// 弾にバラつきを持たせる
								float randomX = static_cast<float>(utility::get_random(-700, 700));
								float randomY = static_cast<float>(utility::get_random(0, 1000));
								float randomZ = static_cast<float>(utility::get_random(-700, 700));
								_vTarget = { _vRelation.x + randomX, _vRelation.y + randomY, _vRelation.z + randomZ };
							}
						}
						// 対空砲の数を合わせる
						if (!_pull) {
							_iPieces = obje->_iPieces;
						}
					}
					else {
						if (obje->_pull == false) {
							// 何個目かの対空砲か記録する
							_iPieces = obje->_iPieces + _iPart;
						}
					}
				}
				if (obje->_finish && _pull) {
					// 兵器化に移行
					_coll = false;
					_pull = false;
					_finish = true;
					obje->_iPieces += _iPossession;
					_stateAAA = State::WEAPON;
				}
				if (_stateAAA == State::WEAPON) {
					// プレイヤーと動きを同化させる
					_vPos = obje->_vPos;
					_vPos.y -= 2.f * _collision._fRadius + static_cast<float>(_iPieces) * _collision._fRadius;
					_fRotatY = obje->_fRotatY + utility::PiOver2;
					_fire = obje->_fire;
				}
			}
			if (obje->GetType() == Type::kEnemyAAA) {
				if (_stateAAA == State::NUM) {
					if (Intersect(obje->_collision, _collision)) {
						if (_iPieces == obje->_iPieces + 1) {
							if (obje->_finish) {
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
						Damage();
					}
				}
			}
		}
	}

	if(_stateAAA == State::PLAY){
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
		if (_iType == 1) {
			rad = utility::degree_to_radian(_fAxialY);
			theta = utility::degree_to_radian(_fAxialX);
			_fRotatX = theta;
		}

		// 弾の進行方向の向きを設定
		_vDir.x = cos(rad);
		_vDir.z = sin(rad);
		_vDir.y = cos(theta);
		_vDir.Normalized();

		// 一定間隔で撃つ
		if (_CT == 0) {
			AddBullet();
			_CT = 10;
		}

		// 三次元極座標(r(length3D),θ(theta),φ(rad))
		sx = _vRelation.x - _vPos.x;
		sy = _vRelation.y - _vPos.y;
		sz = _vRelation.z - _vPos.z;
		length3D = sqrt(sx * sx + sy * sy + sz * sz);
		rad = atan2(sz, sx);
		theta = acos(sy / length3D);

		// モデルの向きの設定用
		_vDir.x = cos(rad);
		_vDir.z = sin(rad);
		_vDir.Normalized();

		// Y軸回転
		_fRotatY = -rad;
		// X軸回転
		float rX = cos(theta);
		float degree = utility::radian_to_degree(rX);
		if (degree >= 0.f && degree <= 40.f) {
			_fRotatX = rX;
		}
		if (_iType == 1) {
			_fRotatX = rX;
		}
	}
	else if(_stateAAA == State::WEAPON){
		// 三次元極座標(r(length3D),θ(theta),φ(rad))
		float sx = _vTarget.x - _vPos.x;
		float sy = _vTarget.y - _vPos.y;
		float sz = _vTarget.z - _vPos.z;
		float length3D = sqrt( sx * sx + sy * sy + sz * sz );
		float rad = atan2( sz,sx );
		float theta = acos( sy / length3D );

		// 弾の進行方向の向きを設定する
		_vDir.x = cos(rad);
		_vDir.z = sin(rad);
		_vDir.y = cos(theta);
		_vDir.Normalized();

		// プレイヤーが射撃していたら一定間隔で撃つ
		if (_fire && _CT == 0) {
			AddBullet();
			_CT = 10;
		}

		// X軸回転
		float rX = cos(theta);
		float degree = utility::radian_to_degree(rX);
		if (degree >= 0.f && degree <= 40.f) {
			_fRotatX = rX;
		}
	}
	else if(_stateAAA == State::NUM){
		// イベント用コリジョンを移動
		float distance = _collision._fRadius + _collisionEvent._fRadius;
		_vEvent = { _vPos.x, _vPos.y + distance, _vPos.z };
		_vDir = { 1.f, 0.f, 0.f };
	}

	_collision._fRadius = 300.f * _fScale;
	_collisionEvent._fRadius = 500.f * _fScale;
	_collisionSearch._fRadius = _collision._fRadius * 70.f;
	UpdateCollision();   // コリジョンアップデート

	return true;
}

void EnemyAAA::Damage() {
	--_iLife;
}

bool EnemyAAA::Draw()
{
	base::Draw();

	VECTOR pos = ToDX(_vPos);
	// モデル拡大
	MV1SetScale(_handle_body, VGet(_fScale, _fScale, _fScale));
	MV1SetScale(_handle_turret, VGet(_fScale, _fScale, _fScale));
	// モデル回転
	MV1SetRotationXYZ(_handle_body, VGet(0.f,_fRotatY,0.f));
	MV1SetRotationZYAxis(_handle_turret, VGet(-(_vDir.z), 0.f, _vDir.x), VGet(0.f, 1.f, 0.f), _fRotatX);
	// モデル移動
	MV1SetPosition(_handle_body, pos);
	MV1SetPosition(_handle_turret, VGet(pos.x, pos.y + 40.f, pos.z));
	// モデル描画
	MV1DrawModel(_handle_body);
	MV1DrawModel(_handle_turret);

	// コリジョン描画
	if (!((ModeMainGame&)_mode)._dbgCollisionDraw) {
		if (_coll) {
			vector4 color = { 255, 255, 255 };
			DrawCollision(color);
			if (!_finish) {
				DrawCollisionEvent(color);
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
		else {
			if (_stateAAA != State::NUM) {
				vector4 color = { 255, 255, 255 };
				DrawCollisionSearch(color);
			}
		}
	}

	return true;
}

void EnemyAAA::GetSearch() {
	for (auto&& obje : _mode.GetObjectServer3D().GetObjects()) {
		if (obje->GetType() == Type::kPlayer) {
			if (IsSearch(*obje)) {
				_get = true;
			}
			else {
				_get = false;
			}
		}
	}
	if (!_get) {
		_coll = false;
		if (_stateAAA != State::NUM) {
			_stateAAA = State::EVENT;
		}
	}
}

void EnemyAAA::AddBullet() {
	vector4 vBullet = { _vPos.x, _vPos.y + 100.f, _vPos.z };
	auto bullet = std::make_shared<Bullet>(_game, _mode);
	bullet->SetPosition(vBullet);
	bullet->SetDir(_vDir);
	_mode.GetObjectServer3D().Add(bullet);
}

void EnemyAAA::AddPieces(int pile_num) {
	for (auto i = 0; i < pile_num; ++i) {
		// タワー状に配置する
		vector4 vPiece = { _vPos.x, _vPos.y - _collision._fRadius * static_cast<float>(i + 1), _vPos.z};
		auto piece = std::make_shared<EnemyAAA>(_game, _mode, 0, 0, 0, vPiece);
		piece->_stateAAA = State::NUM;
		piece->_coll = false;
		piece->_iPart = i + 1;   // それぞれが何個目かを記憶
		_mode.GetObjectServer3D().Add(piece);
	}
}