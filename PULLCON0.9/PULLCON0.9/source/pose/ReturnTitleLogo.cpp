#include "ReturnTitleLogo.h"
ReturnTitleLogo::ReturnTitleLogo(): ActorBase2d()
{
	Init();
}

ReturnTitleLogo::~ReturnTitleLogo()
{    // 作成したフォントデータを削除する
	DeleteFontToHandle( FontHandle );
}

void ReturnTitleLogo::Init()
{
	ActorBase2d::Init();

	_pos = {0.0f,157.0f};
	_size = {166.0f,86.0f};
	_colPos = {0.0f,0.0f};
	_colSize = {166.0f,86.0f};
	_spd = 0;
			// 　デフォルトのフォントで、サイズ４０、太さ３のフォントを作成し
	// 作成したデータの識別番号を変数 FontHandle に保存する
	FontHandle = CreateFontToHandle( NULL,32,3 );
}

bool ReturnTitleLogo::Update( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Update( game,mode );
	UpdateCollision();	// コリジョン更新
	return true;
}


bool ReturnTitleLogo::Draw( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Draw( game,mode );
	DrawStringToHandle( _pos.IntX(),_pos.IntY(),"タイトルに戻る",GetColor( 0,255,0 ),FontHandle );
	DrawCollision();	// コリジョン描画
	return true;
}
