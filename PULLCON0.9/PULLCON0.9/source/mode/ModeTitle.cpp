#include "ModeTitle.h"
#include "../ApplicationMain.h"

#include "../title/TitlePlayer.h"
#include "../title/TitleLogo.h"

#include "../title/CreditLogo.h"
#include "../title/CreditGuid.h"
#include "../title/StartLogo.h"
#include "../title/StartGuid.h"
#include "../title/EndLogo.h"
#include "../title/EndGuid.h"
ModeTitle::ModeTitle(ApplicationBase& game,int layer)
	:base(game,layer)
{
	auto titlelogo = std::make_shared<TitleLogo>(game,*this);
	_objectServer.Add( titlelogo );

	auto creditlogo = std::make_shared<CreditLogo>( game,*this );
	_objectServer.Add( creditlogo );
	auto startlogo = std::make_shared<StartLogo>( game,*this );
	_objectServer.Add( startlogo );
	auto endlogo = std::make_shared<EndLogo>( game,*this );
	_objectServer.Add( endlogo );

	auto creditguid = std::make_shared<CreditGuid>( game,*this );
	_objectServer.Add( creditguid );
	auto startguid = std::make_shared<StartGuid>( game,*this );
	_objectServer.Add( startguid );
	auto endguid = std::make_shared<EndGuid>( game,*this );
	_objectServer.Add( endguid );

	auto player = std::make_shared<TitlePlayer>( game,*this );
	_objectServer.Add( player );
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
	_objectServer.Update();
	return true;
}

bool ModeTitle::Draw()
{
	base::Draw();
	_objectServer.Draw( );
	return true;
}
