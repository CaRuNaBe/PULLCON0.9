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
	object_out_game.Add( titlelogo );

	auto creditlogo = std::make_shared<CreditLogo>( game,*this );
	object_out_game.Add( creditlogo );
	auto startlogo = std::make_shared<StartLogo>( game,*this );
	object_out_game.Add( startlogo );
	auto endlogo = std::make_shared<EndLogo>( game,*this );
	object_out_game.Add( endlogo );

	auto creditguid = std::make_shared<CreditGuid>( game,*this );
	object_out_game.Add( creditguid );
	auto startguid = std::make_shared<StartGuid>( game,*this );
	object_out_game.Add( startguid );
	auto endguid = std::make_shared<EndGuid>( game,*this );
	object_out_game.Add( endguid );

	auto player = std::make_shared<TitlePlayer>( game,*this );
	object_out_game.Add( player );
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
	object_out_game.Update();
	return true;
}

bool ModeTitle::Draw()
{
	base::Draw();
	object_out_game.Draw( );
	return true;
}
