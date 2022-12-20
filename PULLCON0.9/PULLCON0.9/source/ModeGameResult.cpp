#include "ModeGameResult.h"
#include "ApplicationMain.h"

ModeGameResult::ModeGameResult(ApplicationBase& game,int layer)
	:base(game,layer)
{

};

ModeGameResult::~ModeGameResult()
{};

bool ModeGameResult::Initialize()
{
	if(!base::Initialize())
	{
		return false;
	}
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

