#include "SkySphere.h"
#include "../ApplicationGlobal.h"
SkySphere::SkySphere(ApplicationBase& game, int layer, ModeMainGame& mode, int objectid)
	:ActorMainGame(game, layer, mode)
{
	_handle = ResourceServer::LoadMV1Model(gGlobal.object_pass_date->GetScriptLine(objectid));
	Initialize();
}

SkySphere::~SkySphere()
{
	MV1DeleteModel(_handle);
}

void SkySphere::Initialize()
{
	ActorMainGame::Initialize();
}

bool SkySphere::Update()
{
	ActorMainGame::Update();
	return true;
}

bool SkySphere::Draw()
{
	ActorMainGame::Draw();
	MV1SetScale(_handle, VGet(10.0f, 10.0f, 10.0f));
	SetFogEnable(FALSE);
	SetUseLighting(FALSE);
	MV1DrawModel(_handle);
	SetUseLighting(TRUE);
	SetFogEnable(TRUE);
	return true;
}
