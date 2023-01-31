#include "ModePause.h"
#include "../ApplicationMain.h"
#include "../pose/PauseLogo.h"
#include "../pose/DescriptionLogo.h"
#include "../pose/RestartLogo.h"
#include "../pose/ReturnTitleLogo.h"
ModePause::ModePause( ApplicationBase& game,int layer )
	:base( game,layer )
{
	auto poselogo = std::make_shared<PauseLogo>( game,*this );
	_objectServer.Add( poselogo );

	auto descriptionlogo = std::make_shared<DescriptionLogo>( game,*this );
	_objectServer.Add( descriptionlogo );
	auto restartlogo = std::make_shared<RestartLogo>( game,*this );
	_objectServer.Add( restartlogo );
	auto returntitleLogo = std::make_shared<ReturnTitleLogo>( game,*this );
	_objectServer.Add( returntitleLogo );
};

ModePause::~ModePause()
{};

bool ModePause::Initialize()
{
	if ( !base::Initialize() )
	{
		return false;
	}
	return true;
}

bool ModePause::Update()
{
	base::Update();
	_objectServer.Update( );
	return true;
}

bool ModePause::Draw()
{
	base::Draw();
	_objectServer.Draw( );
	return true;
}

