
#include "ActorBase3D.h"

ActorBase3D::ActorBase3D()
	:base() {
	Init();
}

ActorBase3D::~ActorBase3D() {

}

void ActorBase3D::Init() {
	base::Init();
	_vPos = { 0.f, 0.f ,0.f };
	_vDir = { 0.f, 0.f ,0.f };

	_speed = 0.f;
	_cnt = 0;
	_ST = 0;

}

bool ActorBase3D::Update(ApplicationBase& game, ModeBase& mode) {
	base::Update(game, mode);

	_cnt++;
	if(_ST > 0) {
		_ST--;
	}
	return true;
}

bool ActorBase3D::Draw(ApplicationBase& game, ModeBase& mode) {
	base::Draw(game, mode);
	return true;
}