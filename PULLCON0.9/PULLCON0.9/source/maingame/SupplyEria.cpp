
#include "SupplyEria.h"
#include "../mode/ModeMainGame.h"
SupplyEria::SupplyEria( float _radius )
	:base()
{
	_handle = MV1LoadModel("res/HelicopterBody.mv1");
	radius = _radius;
	Init();
}

SupplyEria::~SupplyEria()
{

}

void SupplyEria::Init()
{
	base::Init();
	_vPos = {7000.f, 100.f, 7000.f};
	_collisionEvent._fRadius = 5000.0f;

}

bool SupplyEria::Update( ApplicationBase& game,ModeBase& mode )
{
	base::Update( game,mode );

	for (auto&& obje : mode.GetObjectServer3D().GetObjects()) {
		if (obje->GetType() == Type::kPlayer) {
			if (Intersect(obje->_collision, _collisionEvent)) {
				_event = true;
				if (_cnt % 10 == 0) {
					obje->_iFuel++;
					if (obje->_iFuel > 100) {
						obje->_iFuel = 100;
					}
				}
			}
		}
	}

	_vEvent = _vPos;

	UpdateCollision();

	return true;
}

bool SupplyEria::Draw( ApplicationBase& game,ModeBase& mode )
{
	base::Draw( game,mode );
	MV1SetScale(_handle, VGet(2.0f, 2.0f, 2.0f));
	MV1SetPosition(_handle, ToDX(_vPos));
	SetUseLighting(FALSE);
	MV1DrawModel(_handle);
	SetUseLighting(TRUE);

	if (!((ModeMainGame&)mode)._dbgCollisionDraw) {
		vector4 color = { 255, 255, 255 };
		DrawCollisionEvent(color);
		if (_event) {
			color = { 0, 255, 0 };
			DrawCollisionEvent(color);
		}
	}

	return true;
}
