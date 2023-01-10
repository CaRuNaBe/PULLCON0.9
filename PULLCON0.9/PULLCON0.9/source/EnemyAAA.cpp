
#include "appframe.h"
#include "EnemyAAA.h"
#include "Bullet.h"

EnemyAAA::EnemyAAA()
	:base()
{
	_handle_body = MV1LoadModel("res/canon_mk1/mvi/cg_Canon_Mk1_dodai.mv1");
	_handle_turret = MV1LoadModel("res/canon_mk1/mvi/cg_Canon_Mk1_houtou.mv1");

	Init();
}

EnemyAAA::~EnemyAAA() {

}

void EnemyAAA::Init() {
	base::Init();
	_rotatX = 0;
	_rotatY = 0;
	_vTarget = { 0.f,0.f,0.f };
	_ST = 30;
}

bool EnemyAAA::Update(ApplicationBase& game, ModeBase& mode) {
	base::Update(game,mode);

	for (auto&& obje : mode.GetObjectServer3D().GetObjects()) {
		if (obje->GetType() == ActorBase3D::Type::kPlayer) {
			_vTarget = obje->_vPos;
			break;
		}
	}
	// �O�����ɍ��W(r(length3D),��(theta),��(rad))
	float sx = _vTarget.x - _vPos.x;
	float sy = 300.f + _vTarget.y - _vPos.y;   // �������_��
	float sz = _vTarget.z - _vPos.z;
	float length3D = sqrt(sx * sx + sy * sy + sz * sz);
	float rad = atan2(sz, sx);
	float theta = acos(sy / length3D);

	_vDir.x = cos(rad);
	_vDir.z = sin(rad);
	_vDir.y = cos(theta);
	_vDir.Normalized();

	if (_ST == 0) {
		AddBullet(mode);
		_ST = 10;
	}

	_rotatY = -rad;
	_rotatX = cos(theta);

	return true;
}

bool EnemyAAA::Draw(ApplicationBase& game, ModeBase& mode) {
	base::Draw(game, mode);

	VECTOR pos = ToDX(_vPos);
	MV1SetRotationXYZ(_handle_body, VGet(0.f,_rotatY,0.f));
	MV1SetRotationZYAxis(_handle_turret, VGet(-(_vDir.z), 0.f, _vDir.x), VGet(0.f, 1.f, 0.f), _rotatX);
	MV1SetPosition(_handle_body, pos);
	MV1SetPosition(_handle_turret, VGet(pos.x, pos.y + 40.f, pos.z));
	MV1DrawModel(_handle_body);
	MV1DrawModel(_handle_turret);

	return true;
}

void EnemyAAA::AddBullet(ModeBase& mode) {
	vector4 vBullet = { _vPos.x, _vPos.y, _vPos.z };
	auto bullet = std::make_shared<Bullet>();
	bullet->SetPosition(vBullet);
	bullet->SetDir(_vDir);
	mode.GetObjectServer3D().Add(bullet);
}