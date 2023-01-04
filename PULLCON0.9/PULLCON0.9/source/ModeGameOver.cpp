#include "ModeGameOver.h"
#include "ApplicationMain.h"

ModeGameOver::ModeGameOver( ApplicationBase& game,int layer )
	:base( game,layer )
{};

ModeGameOver::~ModeGameOver()
{};

bool ModeGameOver::Initialize()
{
	if ( !base::Initialize() )
	{
		return false;
	}
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

