
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
	if(_CT > 0) {
		_CT--;
	}
	if(_ST > 0) {
		_ST--;
	}
	return true;
}

void	ActorBase3D::UpdateCollision()
{
	_collision._vCenter = _vPos;
}

bool	ActorBase3D::IsHitObject(ActorBase3D& object)
{
	// Sphere‚Å“–‚½‚è”»’è
	if (Intersect(object.GetCollision(), _collision))
	{
		return true;
	}
	return false;
}

bool ActorBase3D::Draw(ApplicationBase& game, ModeBase& mode) {
	base::Draw(game, mode);

	return true;
}

void ActorBase3D::DrawCollision()
{
#if _DEBUG
	_collision.Draw(255, 255, 255);
#endif
}