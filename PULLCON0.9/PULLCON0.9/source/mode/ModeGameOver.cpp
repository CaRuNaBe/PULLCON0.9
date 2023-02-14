#include "ModeGameOver.h"
#include "../ApplicationMain.h"

ModeGameOver::ModeGameOver( ApplicationBase& game,int layer )
	:base( game,layer )
{
	Initialize();
};

ModeGameOver::~ModeGameOver()
{
};

bool ModeGameOver::Initialize()
{
	base::Initialize();
	return true;
}

bool ModeGameOver::Update()
{
	base::Update();
	return true;
}

bool ModeGameOver::Draw()
{
	base::Draw();
	return true;
}

bool ModeGameOver::DebugDraw()
{
	base::DebugDraw();
	return true;
};