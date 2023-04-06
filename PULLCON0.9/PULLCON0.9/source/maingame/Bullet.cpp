
#include "Bullet.h"


Bullet::Bullet(ApplicationBase& game, ModeMainGame& mode)
	:base(game, mode) {
	_handleYellow = ResourceServer::LoadMV1Model("res/3D_model/ammo/AmmoModel_Ver1/Ammo.mv1");
	_handleBlue = ResourceServer::LoadMV1Model("res/3D_model/ammo/AmmoModel_Ver1/Ammo_Blue.mv1");
	_handlePurple = ResourceServer::LoadMV1Model("res/3D_model/ammo/AmmoModel_Ver1/Ammo_Purple.mv1");
	_handle = 0;
	Init();
}

Bullet::~Bullet() {
	MV1DeleteModel(_handleBlue);
	MV1DeleteModel(_handlePurple);
	MV1DeleteModel(_handleYellow);
}

void Bullet::Init() {
	base::Init();

	_iDamage = 25;
	_fSpeed = 1200.f;
	_fScale = 3.f;

	_collision._fRadius = 150.f * _fScale;

	_ST = 90;
}

bool Bullet::Update() {
	base::Update();

	// 生存時間
	if (_ST == 0) {
		Damage();
	}

	// 設定された向きに進む
	vector4 _vd = _vDir;
	_vd *= _fSpeed;
	_vPos += _vd;

	_collision._fRadius = 150.f;
	UpdateCollision();    // コリジョンアップデート

	switch (_iType) {
	case 1:
		_handle = _handleBlue;
		break;
	case 2:
		_handle = _handlePurple;
		break;
	default:
		_handle = _handleYellow;
		break;
	}

	return true;
}

void Bullet::Damage() {
	_mode.AddEffectDestroyAmmo(_vPos);
	_mode.GetObjectServer3D().Del(*this);
}

bool Bullet::Draw() {
	base::Draw();

	float length3D = sqrt(_vDir.x * _vDir.x + _vDir.y * _vDir.y + _vDir.z * _vDir.z);
	float theta = acos(_vDir.y / length3D);
	MV1SetScale(_handle, VGet(_fScale, _fScale, _fScale));
	MV1SetRotationZYAxis(_handle, VGet(_vDir.z, 0.f, -(_vDir.x)), VGet(0.f, 1.f, 0.f), theta - utility::PiOver2);
	MV1SetPosition(_handle, ToDX(_vPos));
	MV1DrawModel(_handle);
	// コリジョン描画
	vector4 color = { 255, 255, 255 };
	if (!((ModeMainGame&)_mode)._dbgCollisionDraw) {
		if (_CT == 0) {
			DrawCollision(color);
		}
	}
	return true;
}
