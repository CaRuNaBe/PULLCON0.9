
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
	_vRelation = { 0.f, 0.f ,0.f };
	_vTarget = { 0.f, 0.f ,0.f };
	_vDir = { 0.f, 0.f ,0.f };

	_iFuel = 0;
	_iLife = 0;
	_iDamage = 0;
	_iPieces = 0;
	_fSpeed = 0.f;
	_fScale = 1.f;
	_fRotatX = 0.f;
	_fRotatY = 0.f;
	_coll = true;
	_overlap = false;
	_event = false;
	_pull = false;
	_finish = false;
	_fire = false;
	_cnt = 0;
	_ST = 0;

}

bool ActorBase3D::Update(ApplicationBase& game, ModeBase& mode) {
	base::Update(game, mode);
	// ���t���[��false�ɂ���
	_overlap = false;
	_event = false;
	_fire = false;

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
	_collisionSearch._vCenter = _vPos;
	_collisionEvent._vCenter = _vEvent;
}

bool	ActorBase3D::IsHitObject(ActorBase3D& object)
{
	if(_coll && object._coll == true){
		// Sphere�œ����蔻��
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
		// Sphere�œ����蔻��
		if (Intersect(object.GetCollisionEvent(), _collision))
		{
			return true;
		}
	}
	return false;
}

bool	ActorBase3D::IsSearch(ActorBase3D& object)
{
	// Sphere�œ����蔻��
	if (Intersect(object.GetCollisionSearch(), _collision))
	{
		return true;
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
	// ���C�e�B���O�v�Z
	SetUseLighting(FALSE);
	_collision.Draw(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
	SetUseLighting(TRUE);
#endif
}

void ActorBase3D::DrawCollisionEvent(vector4 color)
{
#if _DEBUG
	// ���C�e�B���O�v�Z
	SetUseLighting(FALSE);
	_collisionEvent.Draw(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
	SetUseLighting(TRUE);
#endif
}

void ActorBase3D::DrawCollisionSearch(vector4 color)
{
#if _DEBUG
	// ���C�e�B���O�v�Z
	SetUseLighting(FALSE);
	_collisionSearch.Draw(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
	SetUseLighting(TRUE);
#endif
}