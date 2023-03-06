#include "GameStage.h"
#include "../ApplicationGlobal.h"
GameStage::GameStage( ApplicationBase& game,ModeMainGame& mode,int stageid )
	:base( game,mode )
{
	Init();
	_handle = ResourceServer::LoadMV1Model( gGlobal.object_pass_date->GetScriptLine( stageid ).c_str() );
	MV1SetupCollInfo(_handle, 0, 16, 16, 16);
}

GameStage::~GameStage()
{}

void GameStage::Init()
{
	base::Init();
}

bool GameStage::Update()
{
	base::Update();
	return true;
}

bool GameStage::Draw()
{
	base::Draw();
	SetUseLighting(TRUE);
	MV1DrawModel( _handle );
	SetUseLighting(TRUE);
	return true;
}
