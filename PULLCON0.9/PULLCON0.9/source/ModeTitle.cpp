#include "ModeTitle.h"
#include "ApplicationMain.h"
#include "TitlePlayer.h"
ModeTitle::ModeTitle(ApplicationBase& game,int layer)
	:base(game,layer)
{
	auto player = std::make_shared<TitlePlayer>();
	_objectServer.Add(player);
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

