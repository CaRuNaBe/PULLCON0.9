
#include "appframe.h"
#include "EnemyAAA.h"
#include "Bullet.h"

EnemyAAA::EnemyAAA()
	:base()
{
	_handle = MV1LoadModel("res/canon_mk1/mvi/cg_Canon_Mk1.mv1");

	Init();
}

EnemyAAA::~EnemyAAA() {

}

void EnemyAAA::Init() {
	base::Init();
	_rotatX = 0;
	_rotatY = 0;
	_vTer = { 1.f,0.f,0.f };
	_ST = 30;
}

bool EnemyAAA::Update(ApplicationBase& game, ModeBase& mode) {
	base::Update(game,mode);

	// éOéüå≥ã…ç¿ïW(r(length3D),É∆(theta),É”(rad))
	float sx = _vTer.x;
	float sy = _vTer.y;
	float sz = _vTer.z;
	float length3D = sqrt(sx * sx + sy * sy + sz * sz);
	float rad = atan2(sz, sx);
	float theta = acos(sy / length3D);

	_vDir.x = cos(rad);
	_vDir.z = sin(rad);
	_vDir.y = cos(theta);

	if (_ST == 0) {
		AddBullet(mode);
		_ST = 30;
	}

	return true;
}

bool EnemyAAA::Draw(ApplicationBase& game, ModeBase& mode) {
	base::Draw(game, mode);

	MV1SetPosition(_handle, ToDX(_vPos));
	MV1DrawModel(_handle);

	return true;
}

void EnemyAAA::AddBullet(ModeBase& mode) {
	vector4 vBullet = { _vPos.x, _vPos.y, _vPos.z };
	auto bullet = std::make_shared<Bullet>();
	bullet->SetPosition(vBullet);
	bullet->SetDir(_vDir);
	mode.GetObjectServer3D().Add(bullet);
}