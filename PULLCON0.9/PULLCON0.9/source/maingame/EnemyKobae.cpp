#include  "EnemyKobae.h"
#include  "Bullet.h"
#include  "../mode/ModeMainGame.h"
namespace {
	//constexpr int GUNSHIP_ID;
}
EnemyKobae::EnemyKobae(ApplicationBase& game, ModeBase& mode)
	:base(game, mode)
{
	Init();
}

EnemyKobae::~EnemyKobae() {

}

void EnemyKobae::Init() {
	base::Init();

	_handle = ResourceServer::LoadMV1Model("res/enemy/skyhunters/mv1/cg_SkyHunters_KOBAE.mv1");

	_stateEnemyKobae = State::WAIT;

	_vPos = { 0.f, 10000.f, 50000.f };
	_vEvent = _vPos;
	_fScale = 2.f;
	_fSpeed = 200.f;
	_collision._fRadius = 500.f * _fScale;
	_collisionEvent._fRadius = _collision._fRadius * 13.f * _fScale;
	_collisionSearch._fRadius = _collisionEvent._fRadius * 2.f;

	_iLife = 100;

}

bool EnemyKobae::Update() {
	base::Update();


	// �O�����ɍ��W(r(length3D),��(theta),��(rad))
	float sx = 0.f, sz = 0.f, sy = 0.f;
	float length3D = 0.f;
	float rad = 0.f;
	float theta = 0.f;

	for (auto&& obje : _mode.GetObjectServer3D().GetObjects()) {
		if (obje->GetType() == Type::kPlayer
			|| obje->GetType() == Type::kBullet) {
			if (obje->GetType() == Type::kPlayer) {
				if (IsSearch(*obje)) {
					if (_stateEnemyKobae == State::WAIT) {
						_vRelation = obje->_vPos;
						SetVelocity();
						_stateEnemyKobae = State::PLAY;
					}
				}
				else {
					if (_ST == 0) {
						_vRelation = obje->_vPos;
						SetVelocity();
						_stateEnemyKobae = State::PLAY;
						_ST = 300;
					}
				}
				if (Intersect(_collisionEvent, obje->_collision)) {
					_fire = true;
					_vTarget = obje->_vPos;
					// �e�Ƀo��������������
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

	// �O�����ɍ��W
	sx = _vTarget.x - _vPos.x;
	sz = _vTarget.z - _vPos.z;
	sy = _vTarget.y - _vPos.y;
	length3D = sqrt(sx * sx + sy * sy + sz * sz);
	rad = atan2(sz, sx);
	theta = acos(sy / length3D);

	// �e�̐i�s�����̌�����ݒ�
	_vDir.x = cos(rad);
	_vDir.z = sin(rad);
	_vDir.y = cos(theta);
	_vDir.Normalized();

	// ���Ԋu�Œe������
	if (_fire && _CT == 0) {
		AddBullet();
		_CT = 3;
	}

	// ���x���ړ�����
	if (_vPos.y < 6000.f && _vVelocity.y < 0.f) {
		_vVelocity.y = 0.f;
	}
	_vPos += _vVelocity * _fSpeed;

	if (_iLife < 0) {
		Damage();
	}

	_collision._fRadius = 500.f * _fScale;
	_collisionEvent._fRadius = _collision._fRadius * 13.f * _fScale;
	_collisionSearch._fRadius = _collisionEvent._fRadius * 2.f;
	_vEvent = _vPos;
	UpdateCollision();  // �R���W�����X�V

	return true;
}

void EnemyKobae::Damage() {
	_mode.GetObjectServer3D().Del(*this);
}

bool EnemyKobae::Draw() {
	base::Draw();

	// ���f���g��
	MV1SetScale(_handle, VGet(_fScale, _fScale, _fScale));
	// ���f����]
	MV1SetRotationYUseDir(_handle, ToDX(_vVelocity), 0.f);
	// ���f���ړ�
	MV1SetPosition(_handle, ToDX(_vPos));
	// ���f���`��
	MV1DrawModel(_handle);

	// �R���W�����`��
	vector4 color = { 255,255,255 };
	if (!((ModeMainGame&)_mode)._dbgCollisionDraw) {
		DrawCollision(color);
		DrawCollisionEvent(color);
		DrawCollisionSearch(color);
		if (_overlap) {
			color = { 255, 0, 0 };
			DrawCollision(color);
		}
	}
	return true;
}

void EnemyKobae::SetVelocity() {
	// �O�����ɍ��W
	float sx = _vRelation.x - _vPos.x;
	float sz = _vRelation.z - _vPos.z;
	float sy = _vRelation.y - _vPos.y;
	float length3D = sqrt(sx * sx + sy * sy + sz * sz);
	float rad = atan2(sz, sx);
	float theta = acos(sy / length3D);

	float randomDeg = static_cast<float>(utility::get_random(-30, 30));
	float randomRad = utility::degree_to_radian(randomDeg);
	// ���f���̐i�s�����ݒ�p
	_vVelocity.x = cos(rad + randomRad);
	_vVelocity.z = sin(rad + randomRad);
	_vVelocity.y = cos(theta);
	_vVelocity.Normalized();
}


void EnemyKobae::AddBullet() {
	vector4 vBullet = { _vPos.x, _vPos.y - 500.f, _vPos.z };
	auto bullet = std::make_shared<Bullet>(_game, _mode);
	bullet->SetPosition(vBullet);
	bullet->SetDir(_vDir);
	_mode.GetObjectServer3D().Add(bullet);
}