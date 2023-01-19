
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
	_vEvent = { 0.f, 0.f ,0.f };
	_vDir = { 0.f, 0.f ,0.f };
	_vRelation = { 0.f, 0.f ,0.f };

	_speed = 0.f;
	_coll = true;
	_overlap = false;
	_event = false;
	_pull = false;
	_finish = false;
	_cnt = 0;
	_ST = 0;

}

bool ActorBase3D::Update(ApplicationBase& game, ModeBase& mode) {
	base::Update(game, mode);

	_overlap = false;
	_event = false;

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
	_collisionEvent._vCenter = _vEvent;
}

bool	ActorBase3D::IsHitObject(ActorBase3D& object)
{
	if(_coll && object._coll == true){
		// Sphereで当たり判定
		if (Intersect(object.GetCollision(), _collision))
		{
			return true;
		}
	}
	return false;
}

bool	ActorBase3D::IsHitEvent(ActorBase3D& object)
{
	if (_coll && object._coll == true) {
		// Sphereで当たり判定
		if (Intersect(object.GetCollisionEvent(), _collision))
		{
			return true;
		}
	}
	return false;
}

bool ActorBase3D::Draw(ApplicationBase& game, ModeBase& mode) {
	base::Draw(game, mode);

	return true;
}

void ActorBase3D::DrawCollision(vector4 color)
{
#if _DEBUG
	// ライティング計算
	SetUseLighting(FALSE);
	_collision.Draw(static_cast<float>(color.x), static_cast<float>(color.y), static_cast<float>(color.z));
	SetUseLighting(TRUE);
#endif
}

void ActorBase3D::DrawCollisionEvent(vector4 color)
{
#if _DEBUG
	// ライティング計算
	SetUseLighting(FALSE);
	_collisionEvent.Draw(static_cast<float>(color.x), static_cast<float>(color.y), static_cast<float>(color.z));
	SetUseLighting(TRUE);
#endif
}