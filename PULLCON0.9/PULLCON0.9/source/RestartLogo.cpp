#include "RestartLogo.h"
RestartLogo::RestartLogo(): ActorBase2d()
{
	Init();
}

RestartLogo::~RestartLogo()
{    // 作成したフォントデータを削除する
	DeleteFontToHandle( FontHandle );
}

void RestartLogo::Init()
{
	ActorBase2d::Init();

	_pos = {0.0f,128.0f};
	_size = {166.0f,86.0f};
	_colPos = {0.0f,0.0f};
	_colSize = {166.0f,86.0f};
	_spd = 0;
	// 作成したデータの識別番号を変数 FontHandle に保存する
	FontHandle = CreateFontToHandle( NULL,32,3 );
}

bool RestartLogo::Update( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Update( game,mode );
	UpdateCollision();	// コリジョン更新
	return true;
}


bool RestartLogo::Draw( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Draw( game,mode );
	DrawStringToHandle( _pos.IntX(),_pos.IntY(),"ゲームを再開する",GetColor( 0,255,0 ),FontHandle );
	DrawCollision();	// コリジョン描画
	return true;
}
