#include "ModeTest.h"

#include "maingame/Player.h"
#include "maingame/GameStage.h"
#include "maingame/SkySphere.h"
#include "maingame/EnemyAAA.h"
#include "maingame/EnemyKobae.h"
#include "maingame/EnemySkyhunter.h"
#include "maingame/AreaSupply.h"
ModeTest::ModeTest( ApplicationBase& game,int layer )
	:ModeMainGame( game,layer )
{
	auto stage = std::make_shared<GameStage>( _game,*this,33 );
	object_main_game.Add( stage );
	auto skysphere = std::make_shared<SkySphere>( _game,*this,15 );
	object_main_game.Add( skysphere );
	auto player = std::make_shared<Player>( _game,*this );
	player->SetPosition( {0,5000,0} );
	object_main_game.Add( player );

	auto enemy1 = std::make_shared<EnemyAAA>( _game,*this,1,1,1,4,math::vector4( 0,0,0 ) );
	object_main_game.Add( enemy1 );
	auto enemy2 = std::make_shared<EnemyAAA>( _game,*this,2,2,1,4,math::vector4( 2000,0,0 ) );
	object_main_game.Add( enemy2 );
	auto enemy3 = std::make_shared<EnemyAAA>( _game,*this,3,3,1,4,math::vector4( 4000,0,0 ) );
	object_main_game.Add( enemy3 );
	auto enemy4 = std::make_shared<EnemyAAA>( _game,*this,4,4,1,4,math::vector4( 6000,0,0 ) );
	object_main_game.Add( enemy4 );
	auto enemy5 = std::make_shared<EnemyAAA>( _game,*this,5,5,1,4,math::vector4( 8000,0,0 ) );
	object_main_game.Add( enemy5 );
	auto enemy6 = std::make_shared<EnemyAAA>( _game,*this,6,6,1,4,math::vector4( 10000,0,0 ) );
	object_main_game.Add( enemy6 );
	auto enemy7 = std::make_shared<EnemyAAA>( _game,*this,7,7,1,4,math::vector4( 12000,0,0 ) );
	object_main_game.Add( enemy7 );
	auto enemy8 = std::make_shared<EnemyAAA>( _game,*this,8,8,1,4,math::vector4( 14000,0,0 ) );
	object_main_game.Add( enemy8 );
	auto enemy9 = std::make_shared<EnemyAAA>( _game,*this,9,9,1,4,math::vector4( 16000,0,0 ) );
	object_main_game.Add( enemy9 );

	auto sup = std::make_shared<AreaSupply>( _game,*this,2000 );
	object_main_game.Add( sup );
	auto cobae = std::make_shared<EnemyKobae>( _game,*this );
	object_main_game.Add( cobae );

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
{};

bool ModeTest::Initialize()
{

	return true;
}

bool ModeTest::Update()
{
	object_main_game.Update();

	ui_player.Update();
	return true;
}

bool ModeTest::Draw()
{
	object_main_game.Draw();

	ui_player.Draw();
	return true;
}

