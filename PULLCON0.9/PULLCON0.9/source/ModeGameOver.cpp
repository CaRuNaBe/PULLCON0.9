#include "ModeGameOver.h"
#include "ApplicationMain.h"

ModeGameOver::ModeGameOver( ApplicationBase& game,int layer )
	:base( game,layer )
{

};

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
	_objectServer.Update( _game,*this );
	return true;
}

bool ModeGameOver::Draw()
{
	base::Draw();
	_objectServer.Draw( _game,*this );
	return true;
}

