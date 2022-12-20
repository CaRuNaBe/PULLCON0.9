#include "ModePause.h"
#include "ApplicationMain.h"

ModePause::ModePause(ApplicationBase& game,int layer)
	:base(game,layer)
{
};

ModePause::~ModePause()
{};

bool ModePause::Initialize()
{
	if(!base::Initialize())
	{
		return false;
	}
	return true;
}

bool ModePause::Update()
{
	base::Update();
	_objectServer.Update(_game,*this );
	return true;
}

bool ModePause::Draw()
{
	base::Draw();
	_objectServer.Draw(_game,*this );
	return true;
}

