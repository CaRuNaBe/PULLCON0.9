#include "ModeTitle.h"
#include "ApplicationMain.h"

ModeTitle::ModeTitle(ApplicationBase& game,int layer)
	:base(game,layer)
{

};

ModeTitle::~ModeTitle()
{};

bool ModeTitle::Initialize()
{
	if(!base::Initialize())
	{
		return false;
	}
	return true;
}

bool ModeTitle::Update()
{
	base::Update();
	_objectServer.Update(_game);
	return true;
}

bool ModeTitle::Draw()
{
	base::Draw();
	_objectServer.Draw(_game);
	return true;
}

