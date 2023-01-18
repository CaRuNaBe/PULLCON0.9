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
	auto titlelogo = std::make_shared<TitleLogo>();
	_objectServer.Add( titlelogo );

	auto creditlogo = std::make_shared<CreditLogo>();
	_objectServer.Add( creditlogo );
	auto startlogo = std::make_shared<StartLogo>();
	_objectServer.Add( startlogo );
	auto endlogo = std::make_shared<EndLogo>();
	_objectServer.Add( endlogo );

	auto creditguid = std::make_shared<CreditGuid>();
	_objectServer.Add( creditguid );
	auto startguid = std::make_shared<StartGuid>();
	_objectServer.Add( startguid );
	auto endguid = std::make_shared<EndGuid>();
	_objectServer.Add( endguid );

	auto player = std::make_shared<TitlePlayer>();
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
	_objectServer.Update(_game,*this);
	return true;
}

bool ModeTitle::Draw()
{
	base::Draw();
	_objectServer.Draw(_game,*this );
	return true;
}
