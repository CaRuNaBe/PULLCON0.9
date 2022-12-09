
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

ModeGame::ModeGame(ApplicationBase& game,int layer)
	:base(game,layer)
{};

ModeGame::~ModeGame()
{};

bool ModeGame::Initialize()
{
	if(!base::Initialize())
	{
		return false;
	}

	/// <summary>
	/// /
	/// </summary>
	/// <returns></returns>
	return true;
}

bool ModeGame::Update()
{
	base::Update();
	_objectServer.Update(_game);
	return true;
}

bool ModeGame::Draw()
{
	base::Draw();
	_objectServer.Draw(_game);
	return true;
}

