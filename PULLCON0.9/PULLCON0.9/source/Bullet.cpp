
#include "appframe.h"
#include "Bullet.h"

Bullet::Bullet()
	:base()
{

	Init();
}

Bullet::~Bullet() {

}

void Bullet::Init() {
	base::Init();

	_speed = 200.f;
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

	return true;
}

void Bullet::Damage(ModeBase& mode) {
	mode.GetObjectServer3D().Del(*this);
}

bool Bullet::Draw(ApplicationBase& game, ModeBase& mode) {
	base::Draw(game, mode);
	
	DrawSphere3D(ToDX(_vPos), 50.f, 32, GetColor(255, 0, 0), GetColor(0, 0, 0), FALSE);

	return true;
}
