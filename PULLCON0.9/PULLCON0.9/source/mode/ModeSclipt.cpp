#include "ModeSclipt.h"

ModeSclipt::ModeSclipt( ApplicationBase& game,int layer,std::string storyname )
	: ModeBase( game,layer )
{
	Tem_image = ResourceServer::LoadGraph( "res/通信起動中.png" );
	timer = 360;
	story_name = storyname;
}

ModeSclipt::~ModeSclipt()
{
}

// 更新
bool ModeSclipt::Update()
{
	ModeBase::Update();
	timer--;
	if ( timer < 0 )
	{
		_game.GetModeServer()->Del( *this );
	}
	return true;
}

// 描画
bool ModeSclipt::Draw()
{
	ModeBase::Draw();
	DrawBox( 0,0,_game.DispSizeW(),_game.DispSizeH(),GetColor( 255,0,0 ),TRUE );
	DrawGraph( 0,0,Tem_image,TRUE );
	DrawString( 0,0,story_name.c_str(),GetColor( 0,0,0 ) );
	return true;
};