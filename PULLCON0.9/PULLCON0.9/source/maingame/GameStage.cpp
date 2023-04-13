#include "GameStage.h"
#include "../ApplicationGlobal.h"
GameStage::GameStage(ApplicationBase& game, int layer, ModeMainGame& mode, int stageid)
	:ActorMainGame(game, layer, mode)
{
	Initialize();
	_handle = ResourceServer::LoadMV1Model(gGlobal.object_pass_date->GetScriptLine(stageid).c_str());
	MV1SetupCollInfo(_handle, -1, 16, 16, 16);
}

GameStage::~GameStage()
{
	MV1DeleteModel(_handle);
}

void GameStage::Initialize()
{
	ActorMainGame::Initialize();
}

bool GameStage::Update()
{
	ActorMainGame::Update();
	return true;
}

bool GameStage::Draw()
{
	ActorMainGame::Draw();
	SetUseLighting(TRUE);
	MV1DrawModel(_handle);
	SetUseLighting(TRUE);
	return true;
}
