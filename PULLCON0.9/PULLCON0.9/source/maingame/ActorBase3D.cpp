#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
#include "../ApplicationGlobal.h"
ActorBase3D::ActorBase3D(ApplicationBase& game, ModeMainGame& mode)
	:base(game)
	, _mode(mode) {
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
	_vVelocity = { 0.f, 0.f ,0.f };

	_collision = { {0.f,0.f,0.f},0.f };
	_collisionEvent = { {0.f,0.f,0.f},0.f };
	_collisionSearch = { {0.f,0.f,0.f},0.f };

	_iFuel = 0;
	_iLife = 0;
	_iDamage = 0;
	_iPieces = 0;
	_iPart = 0;
	_iType = 0;
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
	_synchronize = false;
	_cnt = 0;
	_CT = 0;
	_ST = 0;

	_fRadius = 0.0f;
}

bool ActorBase3D::Update() {
	base::Update();

	_overlap = false;
	_event = false;
	_fire = false;

	_cnt++;
	if (_CT > 0) {
		_CT--;
	}
	if (_ST > 0) {
		_ST--;
	}
	return true;
}

void	ActorBase3D::UpdateCollision() {
	_collision._vCenter = _vPos;
	_collisionSearch._vCenter = _vPos;
	_collisionEvent._vCenter = _vEvent;
}

bool	ActorBase3D::IsHitObject(ActorBase3D& object) {
	if (_coll && object._coll == true) {
		// Sphereで当たり判定
		if (Intersect(object.GetCollision(), _collision)) {
			return true;
		}
	}
	return false;
}

bool	ActorBase3D::IsHitEvent(ActorBase3D& object) {
	if (_coll && object._coll == true) {
		// Sphereで当たり判定
		if (Intersect(object.GetCollisionEvent(), _collision)) {
			return true;
		}
	}
	return false;
}

bool	ActorBase3D::IsSearch(ActorBase3D& object) {
	// Sphereで当たり判定
	if (Intersect(object.GetCollision(), _collisionSearch)) {
		return true;
	}
	return false;
}

bool ActorBase3D::Draw() {
	base::Draw();
	return true;
}

void ActorBase3D::DrawCollision(vector4 color) {
#if _DEBUG
	// ライティング計算
	SetUseLighting(FALSE);
	_collision.Draw(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
	SetUseLighting(TRUE);
#endif
}

void ActorBase3D::DrawCollisionEvent(vector4 color) {
#if _DEBUG
	// ライティング計算
	SetUseLighting(FALSE);
	_collisionEvent.Draw(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
	SetUseLighting(TRUE);
#endif
}

void ActorBase3D::DrawCollisionSearch(vector4 color) {
#if _DEBUG
	// ライティング計算
	SetUseLighting(FALSE);
	_collisionSearch.Draw(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
	SetUseLighting(TRUE);
#endif
}

void ActorBase3D::DrawCollisionObject(vector4 color) {
#if _DEBUG
	// ライティング計算
	SetUseLighting(FALSE);
	_collision.DrawObject(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
	SetUseLighting(TRUE);
#endif
}

void ActorBase3D::SeGunShotPlay() {
	ChangeVolumeSoundMem(255 * 80 / 100, gGlobal._se["se_gunshot"]);
	if (!(CheckSoundMem(gGlobal._se["se_gunshot"]))) {
		PlaySoundMem(gGlobal._se["se_gunshot"], DX_PLAYTYPE_BACK);
	}
};