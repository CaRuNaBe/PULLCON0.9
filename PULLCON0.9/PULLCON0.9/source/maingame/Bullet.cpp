
#include "Bullet.h"
#include "EffectTrail.h"


Bullet::Bullet( ApplicationBase& game,ModeMainGame& mode)
	:base(game,mode)
{
	_cgDarkPurple = ResourceServer::LoadGraph("res/2D_image/BulletBillBorad/BulletTexture_DarkPurple.png");
	_cgGreen = ResourceServer::LoadGraph("res/2D_image/BulletBillBorad/BulletTexture_Green.png");
	_cgPink = ResourceServer::LoadGraph("res/2D_image/BulletBillBorad/BulletTexture_Pink.png");
	_cgPurple = ResourceServer::LoadGraph("res/2D_image/BulletBillBorad/BulletTexture_Purple.png");
	_cgYellow = ResourceServer::LoadGraph("res/2D_image/BulletBillBorad/BulletTexture_Yellow.png");
	_cg = 0;
	Init();
}

Bullet::~Bullet() {

}

void Bullet::Init() {
	base::Init();

	_iType = 0;
	_iDamage = 1;
	_fSpeed = 800.f;

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

	_iDamage = _fScale;

	_collision._fRadius = 50.f * _fScale;
	UpdateCollision();    // コリジョンアップデート

	switch (_iType) {
	case 1:
		_cg = _cgDarkPurple;
		break;
	case 2:
		_cg = _cgPink;
		break;
	case 3:
		_cg = _cgPurple;
		break;
	case 4:
		_cg = _cgYellow;
		break;
	default:
		_cg = _cgGreen;
		break;
	}

	return true;
}

void Bullet::Damage() {
	_mode.GetObjectServer3D().Del(*this);
}

bool Bullet::Draw() {
	base::Draw();

	float size = 150.f * _fScale;
	DrawBillboard3D(ToDX(_vPos), 0.5f, 0.5f, size, 0.f, _cg, TRUE);

	// コリジョン描画
	vector4 color = { 255, 255, 255 };
	if (!((ModeMainGame&)_mode)._dbgCollisionDraw) {
		if (_CT == 0) {
			DrawCollision(color);
		}
	}
	return true;
}
