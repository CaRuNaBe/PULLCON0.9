
#include "Bullet.h"
#include "EffectTrail.h"
#include "../mode/ModeMainGame.h"

Bullet::Bullet()
	:base()
{
	_handle = MV1LoadModel("res/bullet/model/normalammo/cg_NormalAmmo.mv1");

	Init();
}

Bullet::~Bullet() {

}

void Bullet::Init() {
	base::Init();

	_iDamage = 1;
	_fSpeed = 400.f;
	_animeNo = 0;

	_collision._fRadius = 50.f;

	_CT = 10;
	_ST = 90;
}

bool Bullet::Update(ApplicationBase& game, ModeBase& mode) {
	base::Update(game, mode);

	// 生存時間
	if (_ST == 0) {
		Damage(mode);
	}

	// 設定された向きに進む
	vector4 _vd = _vDir;
	_vd *= _fSpeed;
	_vPos += _vd;

	UpdateCollision();    // コリジョンアップデート

	if (_cnt % 3 == 0) {
		auto effect = std::make_shared<EffectTrail>();
		effect->SetPosition(_vPos);
		mode.GetObjectServer3D().Add(effect);
	}

	return true;
}

void Bullet::Damage(ModeBase& mode) {
	mode.GetObjectServer3D().Del(*this);
}

bool Bullet::Draw(ApplicationBase& game, ModeBase& mode) {
	base::Draw(game, mode);

	// 三次元極座標(r(length3D),θ(theta),φ(camerad))
	float length3D = sqrt(_vDir.x * _vDir.x + _vDir.y * _vDir.y + _vDir.z * _vDir.z);
	float rad = atan2(_vDir.z, _vDir.x);
	float theta = acos(_vDir.y / length3D);

	// モデル拡大
	MV1SetScale(_handle, VGet(_fScale, _fScale, _fScale));
	// モデル回転
	MV1SetRotationZYAxis(_handle, VGet(_vDir.z, 0.f, -(_vDir.x)), VGet(0.f, 1.f, 0.f), theta);
	// モデル移動
	MV1SetPosition(_handle, ToDX(_vPos));
	// モデル描画
	MV1DrawModel(_handle);

	// コリジョン描画
	vector4 color = { 255, 255, 255 };
	if (!((ModeMainGame&)mode)._dbgCollisionDraw) {
		if (_CT == 0) {
			DrawCollision(color);
		}
	}
	return true;
}
