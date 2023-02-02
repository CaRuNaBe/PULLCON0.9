
#include "Bullet.h"
#include "EffectTrail.h"
#include "../mode/ModeMainGame.h"

Bullet::Bullet( ApplicationBase& game,ModeBase& mode)
	:base(game,mode)
{
	//_handle = MV1LoadModel("res/bullet/model/normalammo/cg_NormalAmmo.mv1");
	_cg = ResourceServer::LoadGraph("res/bullet/BulletBillBorad/BulletTexture_Green.png");
	Init();
}

Bullet::~Bullet() {

}

void Bullet::Init() {
	base::Init();

	_iDamage = 1;
	_fSpeed = 400.f;

	_collision._fRadius = 50.f * _fScale;

	_CT = 10;
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

	_collision._fRadius = 50.f * _fScale;
	UpdateCollision();    // コリジョンアップデート

	if (_cnt % 4 == 0) {
		auto effect = std::make_shared<EffectTrail>( _game,_mode);
		effect->SetPosition(_vPos);
		//mode.GetObjectServer3D().Add(effect);
	}

	return true;
}

void Bullet::Damage() {
	_mode.GetObjectServer3D().Del(*this);
}

bool Bullet::Draw() {
	base::Draw();

	// 三次元極座標(r(length3D),θ(theta),φ(camerad))
	float length3D = sqrt(_vDir.x * _vDir.x + _vDir.y * _vDir.y + _vDir.z * _vDir.z);
	float rad = atan2(_vDir.z, _vDir.x);
	float theta = acos(_vDir.y / length3D);

	/*// モデル拡大
	MV1SetScale(_handle, VGet(_fScale, _fScale, _fScale));
	// モデル回転
	MV1SetRotationZYAxis(_handle, VGet(_vDir.z, 0.f, -(_vDir.x)), VGet(0.f, 1.f, 0.f), theta);
	// モデル移動
	MV1SetPosition(_handle, ToDX(_vPos));
	// モデル描画
	MV1DrawModel(_handle);
	*/

	DrawBillboard3D(ToDX(_vPos), 0.5f, 0.5f, 150.f, 0.f, _cg, TRUE);

	// コリジョン描画
	vector4 color = { 255, 255, 255 };
	if (!((ModeMainGame&)_mode)._dbgCollisionDraw) {
		if (_CT == 0) {
			DrawCollision(color);
		}
	}
	return true;
}
