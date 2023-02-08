#include  "EnemySkyhunter.h"
#include "Bullet.h"
#include "../mode/ModeMainGame.h"
namespace
{
	//constexpr int GUNSHIP_ID;
}
EnemySkyhunter::EnemySkyhunter(ApplicationBase& game, ModeBase& mode)
	:base(game, mode)
{
	Init();
}

EnemySkyhunter::~EnemySkyhunter()
{

}

void EnemySkyhunter::Init()
{
	base::Init();

	_handle = MV1LoadModel("res/enemy/skyhunters/mv1/cg_SkyHunters.mv1");

	_stateEnemySkyhunter = State::NUM;

	_vPos = { 0.f, 5000.f, 50000.f };
	_vEvent = _vPos;
	_fScale = 2.f;
	_fSpeed = 150.f;
	_collision._fRadius = 500.f * _fScale;
	_collisionEvent._fRadius = _collision._fRadius * 5.f * _fScale;
	_collisionSearch._fRadius = _collisionEvent._fRadius * 3.f;

	_iLife = 100;

}

bool EnemySkyhunter::Update()
{
	base::Update();

	for (auto&& obje : _mode.GetObjectServer3D().GetObjects()) {
		if (obje->GetType() == Type::kPlayer
			|| obje->GetType() == Type::kBullet) {
			if (obje->GetType() == Type::kPlayer) {
				if (IsSearch(*obje)) {
					
				}
				else {
					if (_ST == 0) {
						_vRelation = obje->_vPos;
						// 三次元極座標(r(length3D),θ(theta),φ(rad))
						float sx = _vRelation.x - _vPos.x;
						float sz = _vRelation.z - _vPos.z;
						float sy = _vRelation.y - _vPos.y;
						float length3D = sqrt(sx * sx + sy * sy + sz * sz);
						float rad = atan2(sz, sx);
						float theta = acos(sy / length3D);

						float randomDeg = static_cast<float>(utility::get_random(-30, 30));
						float randomRad = utility::degree_to_radian(randomDeg);
						// モデルの進行方向設定用
						_vVelocity.x = cos(rad + randomRad);
						_vVelocity.z = sin(rad + randomRad);
						_vVelocity.y = cos(theta);
						_vVelocity.Normalized();
						_ST = 180;
					}
				}
				if (Intersect(_collisionEvent, obje->_collision)) {
					_fire = true;
					_vTarget = obje->_vPos;
					// 弾にバラつきを持たせる
					float randomX = static_cast<float>(utility::get_random(-700, 700));
					float randomY = static_cast<float>(utility::get_random(-700, 1400));
					float randomZ = static_cast<float>(utility::get_random(-700, 700));
					_vTarget = { _vTarget.x + randomX, _vTarget.y + randomY, _vTarget.z + randomZ };
				}
			}
			if (obje->GetType() == Type::kBullet) {
				if (IsHitObject(*obje)) {
					if (obje->_CT == 0) {
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
	float length3D = sqrt(sx * sx + sy * sy + sz * sz);
	float rad = atan2(sz, sx);
	float theta = acos(sy / length3D);

	// 弾の進行方向の向きを設定
	_vDir.x = cos(rad);
	_vDir.z = sin(rad);
	_vDir.y = cos(theta);
	_vDir.Normalized();

	// 一定間隔で撃つ
	if (_fire && _CT == 0) {
		AddBullet();
		_CT = 5;
	}

	if (_vPos.y < 4000.f && _vVelocity.y < 0.f) {
		_vVelocity.y = 0.f;
	}
	
	_vPos += _vVelocity * _fSpeed;

	if (_iLife < 0) {
		Damage(_mode);
	}

	_collision._fRadius = 500.f * _fScale;
	_collisionEvent._fRadius = _collision._fRadius * 13.f * _fScale;
	_collisionSearch._fRadius = _collisionEvent._fRadius * 2.f;
	_vEvent = _vPos;
	UpdateCollision();  // コリジョン更新

	return true;
}

void EnemySkyhunter::Damage(ModeBase& mode)
{
	mode.GetObjectServer3D().Del(*this);
}

bool EnemySkyhunter::Draw()
{
	base::Draw();

	// モデル拡大
	MV1SetScale(_handle, VGet(_fScale, _fScale, _fScale));
	// モデル回転
	MV1SetRotationYUseDir(_handle, ToDX(_vVelocity), 0.f);
	// モデル移動
	MV1SetPosition(_handle, ToDX(_vPos));
	// モデル描画
	MV1DrawModel(_handle);

	// コリジョン描画
	vector4 color = { 255,255,255 };
	if (!((ModeMainGame&)_mode)._dbgCollisionDraw)
	{
		DrawCollision(color);
		DrawCollisionEvent(color);
		DrawCollisionSearch(color);
		if (_overlap)
		{
			color = { 255, 0, 0 };
			DrawCollision(color);
		}
	}
	return true;
}

void EnemySkyhunter::AddBullet() {
	vector4 vBullet = { _vPos.x, _vPos.y - 500.f, _vPos.z };
	auto bullet = std::make_shared<Bullet>(_game, _mode);
	bullet->SetPosition(vBullet);
	bullet->SetDir(_vDir);
	_mode.GetObjectServer3D().Add(bullet);
}