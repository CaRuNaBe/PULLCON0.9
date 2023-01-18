#include "SupplyEria.h"
SupplyEria::SupplyEria()
	:base()
{
	Init();
}

SupplyEria::~SupplyEria()
{

}

void SupplyEria::Init()
{
	base::Init();
	_vPos = {30,0,100};

}

bool SupplyEria::Update( ApplicationBase& game,ModeBase& mode )
{
	base::Update( game,mode );



	return true;
}

bool SupplyEria::Draw( ApplicationBase& game,ModeBase& mode )
{
	base::Draw( game,mode );
	DrawSphere3D( math::ToDX( _vPos ),10000.0f,32,GetColor(255,0,255),GetColor(255,255,255),FALSE);
	return true;
}
