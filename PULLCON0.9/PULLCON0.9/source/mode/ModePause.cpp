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
	object_out_game.Add( poselogo );

	auto descriptionlogo = std::make_shared<DescriptionLogo>( game,*this );
	object_out_game.Add( descriptionlogo );
	auto restartlogo = std::make_shared<RestartLogo>( game,*this );
	object_out_game.Add( restartlogo );
	auto returntitleLogo = std::make_shared<ReturnTitleLogo>( game,*this );
	object_out_game.Add( returntitleLogo );
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
	object_out_game.Update( );
	return true;
}

bool ModePause::Draw()
{
	base::Draw();
	object_out_game.Draw( );
	return true;
}

