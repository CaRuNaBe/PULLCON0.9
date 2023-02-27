#include "SkySphere.h"
#include "../ApplicationGlobal.h"
SkySphere::SkySphere( ApplicationBase& game,ModeMainGame& mode,int objectid )
	:base( game,mode )
{
	_handle = ResourceServer::LoadMV1Model( gGlobal.object_pass_date->GetScriptLine( objectid ).c_str() );
	Init();
}

SkySphere::~SkySphere()
{
}

void SkySphere::Init()
{
	base::Init();
}

bool SkySphere::Update()
{
	base::Update();
	return true;
}

bool SkySphere::Draw()
{
	base::Draw();
	MV1SetScale( _handle,VGet( 10.0f,10.0f,10.0f ) );
	SetUseLighting( FALSE );
	MV1DrawModel( _handle );
	SetUseLighting( TRUE );
	return true;
}
