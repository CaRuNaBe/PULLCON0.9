
#include "ClearObject.h"
#include "../mode/ModeGame.h"

ClearObject::ClearObject()
	:base()
{

	Init();
}

ClearObject::~ClearObject()
{

}

void ClearObject::Init()
{
	base::Init();
	_handle = MV1LoadModel( "res/enemy/gunship/mv1/cg_Gunship.mv1" );
	_vObjective = { 0.f ,5000.f, 15000.f };

	_vPos = { _vObjective.x - 5000.f, _vObjective.y, _vObjective.z };
	_vEvent = _vPos;
	_collision._fRadius = 1400.f;
	_collisionEvent._fRadius = _collision._fRadius * 5.f;

	_iLife = 100;

}

bool ClearObject::Update( ApplicationBase& game,ModeBase& mode )
{
	base::Update( game,mode );

	for (auto&& obje : mode.GetObjectServer3D().GetObjects()) {
		if (obje->GetType() == Type::kPlayer
			|| obje->GetType() == Type::kBullet) {
			if (obje->GetType() == Type::kPlayer) {
				
			}
			if (obje->GetType() == Type::kBullet) {
				if (IsHitObject(*obje)) {
					if (obje->_CT == 0) {
						_CT = 10;
						_overlap = true;
						obje->Damage(mode);
						_iLife -= obje->_iDamage;
					}
				}
			}
		}
	}

	if (_iLife == 0) {
		Damage(mode);
	}

	UpdateCollision();

	return true;
}

void ClearObject::Damage(ModeBase& mode) {
	((ModeGame&)mode)._clear = true;
	mode.GetObjectServer3D().Del(*this);
}

bool ClearObject::Draw( ApplicationBase& game,ModeBase& mode )
{
	base::Draw( game,mode );
	DrawSphere3D(ToDX(_vObjective), 100.f, 8, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
	MV1SetScale(_handle, VGet(3.0f, 3.0f, 3.0f));
	MV1SetPosition(_handle, ToDX(_vPos));
	MV1DrawModel(_handle);

	vector4 color = { 255,255,255 };
	DrawCollision(color);
	DrawCollisionEvent(color);
	if (_overlap) {
		color = { 255, 0, 0 };
		DrawCollision(color);
	}

	return true;
}
