#include "ModeGameResult.h"
#include "../ApplicationMain.h"

ModeGameResult::ModeGameResult( ApplicationBase& game,int layer )
	:base( game,layer )
{
	Initialize();
};

ModeGameResult::~ModeGameResult()
{
};

bool ModeGameResult::Initialize()
{
	base::Initialize();
	return true;
}

bool ModeGameResult::Update()
{
	base::Update();
	return true;
}

bool ModeGameResult::Draw()
{
	base::Draw();
	return true;
}

bool ModeGameResult::DebugDraw()
{
	base::DebugDraw();
	return true;
};