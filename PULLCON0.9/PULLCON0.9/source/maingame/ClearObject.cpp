#include "ClearObject.h"
ClearObject::ClearObject()
	:base()
{
	Init();
}

ClearObject::~ClearObject()
{}

void ClearObject::Init()
{
	base::Init();
	_handle = MV1LoadModel( "res/enemy/gunship/mv1/cg_Gunship.mv1" );
	_vPos = {0,15000,0};
}

bool ClearObject::Update( ApplicationBase& game,ModeBase& mode )
{
	base::Update( game,mode );
	return true;
}

bool ClearObject::Draw( ApplicationBase& game,ModeBase& mode )
{
	base::Draw( game,mode );
	MV1SetScale( _handle,VGet( 5.0f,5.0f,5.0f ) );
	MV1SetPosition( _handle,math::ToDX( _vPos ) );
	MV1DrawModel( _handle );
	return true;
}
