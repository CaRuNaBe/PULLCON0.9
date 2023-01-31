
#include "ClearObject.h"
#include "../mode/ModeGame.h"
#include "../mode/ModeMainGame.h"

ClearObject::ClearObject( ApplicationBase& game,ModeBase& mode,float _radius )
	:base( game,mode )
{
	radius = _radius;
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

bool ClearObject::Update(  )
{
	base::Update( );

	for (auto&& obje : _mode.GetObjectServer3D().GetObjects()) {
		if (obje->GetType() == Type::kPlayer
			|| obje->GetType() == Type::kBullet) {
			if (obje->GetType() == Type::kPlayer) {
				
			}
			if (obje->GetType() == Type::kBullet) {
				if (IsHitObject(*obje)) {
					if (obje->_CT == 0) {
						_CT = 10;
						_overlap = true;
						obje->Damage();
						_iLife -= obje->_iDamage;
					}
				}
			}
		}
	}

	if (_iLife < 0) {
		Damage(_mode);
	}

	_vEvent = _vPos;
	UpdateCollision();

	return true;
}

void ClearObject::Damage(ModeBase& mode) {
	((ModeMainGame&)mode)._clear = true;
	mode.GetObjectServer3D().Del(*this);
}

bool ClearObject::Draw(  )
{
	base::Draw();
	//DrawSphere3D(ToDX(_vObjective), 100.f, 8, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
	MV1SetScale(_handle, VGet(3.0f, 3.0f, 3.0f));
	MV1SetPosition(_handle, ToDX(_vPos));
	MV1DrawModel(_handle);

	vector4 color = { 255,255,255 };
	if (!((ModeMainGame&)_mode)._dbgCollisionDraw) {
		DrawCollision(color);
		DrawCollisionEvent(color);
		if (_overlap) {
			color = { 255, 0, 0 };
			DrawCollision(color);
		}
	}
	return true;
}
