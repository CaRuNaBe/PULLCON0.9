#include "ModeTest.h"

#include "maingame/Player.h"
#include "maingame/GameStage.h"
#include "maingame/SkySphere.h"
#include "maingame/EnemyAAA.h"



ModeTest::ModeTest( ApplicationBase& game,int layer )
	:ModeBase( game,layer )
{
	auto stage = std::make_shared<GameStage>( _game,*this,38 );
	object_main_game.Add( stage );
	auto skysphere = std::make_shared<SkySphere>( _game,*this,15 );
	object_main_game.Add( skysphere );
	auto player = std::make_shared<Player>( _game,*this );
	player->SetPosition( {0,5000,0} );
	object_main_game.Add( player );
	auto enemy1 = std::make_shared<EnemyAAA>( _game,*this,2,3,6,math::vector4( 0,0,0 ) );
	object_main_game.Add( enemy1 );

	auto enemy = std::make_shared<EnemyAAA>( _game,*this,2,3,6,math::vector4( 0,0,0 ) );
	enemy->SetPosition( {5000,0,0} );
	object_main_game.Add( enemy );
	auto fuel_gage = std::make_unique<UIFuelGage>( _game,0,*this );
	ui_player.Add( std::move( fuel_gage ) );
	auto hp_gage = std::make_unique<UIHpGage>( _game,1,*this );
	ui_player.Add( std::move( hp_gage ) );
	auto cursor = std::make_unique<UICursor>( _game,2,*this );
	ui_player.Add( std::move( cursor ) );
	auto pullgage = std::make_unique<UIPullGage>( _game,3,*this );
	ui_player.Add( std::move( pullgage ) );

};

ModeTest::~ModeTest()
{
};

bool ModeTest::Initialize()
{
	if ( !ModeBase::Initialize() )
	{
		return false;
	}
	return true;
}

bool ModeTest::Update()
{
	ModeBase::Update();
	object_main_game.Update();

	ui_player.Update();
	return true;
}

bool ModeTest::Draw()
{
	ModeBase::Draw();
	object_main_game.Draw();

	ui_player.Draw();
	return true;
}

