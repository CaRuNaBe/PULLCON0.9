#include "ModeTitle.h"
#include "ApplicationMain.h"

#include "TitlePlayer.h"
#include "TitleLogo.h"
#include "CreditLogo.h"
#include "StartLogo.h"
#include "EndLogo.h"
ModeTitle::ModeTitle(ApplicationBase& game,int layer)
	:base(game,layer)
	,_objectServer()
{
	auto titlelogo = std::make_shared<TitleLogo>();
	_objectServer.Add( titlelogo );
	auto creditlogo = std::make_shared<CreditLogo>();
	_objectServer.Add( creditlogo );
	auto startlogo = std::make_shared<StartLogo>();
	_objectServer.Add( startlogo );
	auto endlogo = std::make_shared<EndLogo>();
	_objectServer.Add( endlogo );
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

