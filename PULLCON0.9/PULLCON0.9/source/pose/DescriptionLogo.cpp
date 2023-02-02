#include "DescriptionLogo.h"
DescriptionLogo::DescriptionLogo( ApplicationBase& game,ModeBase& mode ): ActorBase2d( game,mode )
{
	Init();
}

DescriptionLogo::~DescriptionLogo()
{    // 作成したフォントデータを削除する
	DeleteFontToHandle( FontHandle );
}

void DescriptionLogo::Init()
{
	ActorBase2d::Init();

	_pos = {890.0f,850.0f};
	_size = {166.0f,86.0f};
	_colPos = {0.0f,0.0f};
	_colSize = {166.0f,86.0f};
	_spd = 0;
	// 作成したデータの識別番号を変数 FontHandle に保存する
	FontHandle = CreateFontToHandle( NULL,32,3 );
}

bool DescriptionLogo::Update()
{
	ActorBase2d::Update();
	//ChangeFontType( フォントタイプ );
	UpdateCollision();	// コリジョン更新
	return true;
}


bool DescriptionLogo::Draw()
{
	ActorBase2d::Draw();
	DrawStringToHandle( _pos.IntX(),_pos.IntY(),"操作説明",GetColor( 0,255,0 ),FontHandle );
	DrawCollision();	// コリジョン描画
	return true;
}