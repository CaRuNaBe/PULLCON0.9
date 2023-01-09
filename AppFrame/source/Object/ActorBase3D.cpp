
#include "ActorBase3D.h"

ActorBase::ActorBase()
	:base() {
	Init();
}

ActorBase::~ActorBase() {

}

void ActorBase::Init() {
	base::Init();
	_vPos = { 0.f, 0.f ,0.f };
	_vDir = { 0.f, 0.f ,0.f };

	_speed = 0.f;
	_cnt = 0;
	_ST = 0;

}

bool ActorBase::Update(ApplicationBase& game, ModeBase& mode) {
	base::Update(game, mode);

	_cnt++;
	if(_ST > 0) {
		_ST--;
	}
	return true;
}

bool ActorBase::Draw(ApplicationBase& game, ModeBase& mode) {
	base::Draw(game, mode);
	return true;
}