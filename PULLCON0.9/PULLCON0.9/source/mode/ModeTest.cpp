#include "ModeTest.h"

#include "../maingame/Player.h"
#include "../maingame/GameStage.h"
#include "../maingame/SkySphere.h"
ModeTest::ModeTest( ApplicationBase& game,int layer )
	:base( game,layer )
{
	auto stage = std::make_shared<GameStage>( _game,*this, 36);
	object_main_game.Add( stage );
	auto skysphere = std::make_shared<SkySphere>( _game,*this,15 );
	object_main_game.Add( skysphere );
	auto player = std::make_shared<Player>( _game,*this );
	object_main_game.Add( player );
};

ModeTest::~ModeTest()
{
};

bool ModeTest::Initialize()
{
	if ( !base::Initialize() )
	{
		return false;
	}
	return true;
}

bool ModeTest::Update()
{
	base::Update();
	object_main_game.Update();
	return true;
}

bool ModeTest::Draw()
{
	base::Draw();

	object_main_game.Draw();

	return true;
}

