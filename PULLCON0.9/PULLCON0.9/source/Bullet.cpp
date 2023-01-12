
#include "appframe.h"
#include "Bullet.h"

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

	_speed = 200.f;

	_collision._fRadius = 50.f;

	_CT = 10;
	_ST = 90;
}

bool Bullet::Update(ApplicationBase& game, ModeBase& mode) {
	base::Update(game, mode);

	vector4 _vd = _vDir;
	_vd *= _speed;
	_vPos += _vd;

	if(_ST == 0) {
		Damage(mode);
	}

		UpdateCollision();

	return true;
}

void Bullet::Damage(ModeBase& mode) {
	mode.GetObjectServer3D().Del(*this);
}

bool Bullet::Draw(ApplicationBase& game, ModeBase& mode) {
	base::Draw(game, mode);

	// éOéüå≥ã…ç¿ïW(r(length3D),É∆(theta),É”(camerad))
	float length3D = sqrt(_vDir.x * _vDir.x + _vDir.y * _vDir.y + _vDir.z * _vDir.z);
	float rad = atan2(_vDir.z, _vDir.x);
	float theta = acos(_vDir.y / length3D);

	MV1SetScale(_handle, VGet(3.f, 3.f, 3.f));
	MV1SetRotationZYAxis(_handle, VGet(_vDir.z, 0.f, -(_vDir.x)), VGet(0.f, 1.f, 0.f), theta);
	MV1SetPosition(_handle, ToDX(_vPos));
	MV1DrawModel(_handle);
	//DrawSphere3D(ToDX(_vPos), 50.f, 4, GetColor(255, 0, 0), GetColor(0, 0, 0), FALSE);

	DrawCollision();

	return true;
}
