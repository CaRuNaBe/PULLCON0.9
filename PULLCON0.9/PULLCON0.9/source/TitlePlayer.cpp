#include "Dxlib.h"
#include "TitlePlayer.h"


TitlePlayer::TitlePlayer()
	: ActorBase2d()
{
	_cg = ResourceServer::LoadGraph( "res/title/cg_Heli.png" );
	Init();
}

TitlePlayer::~TitlePlayer()
{}

void TitlePlayer::Init()
{
	ActorBase2d::Init();

	// プレイヤー情報の初期化
	_pos.x = static_cast<float>(utility::get_random( 0,1920 ));
	_pos.y = static_cast<float>(utility::get_random( 0,1000 ));
	_size.x = 206.0f;
	_size.y = 175.0f;
	_colPos.x = 0.0f;
	_colPos.y = 0.0f;
	_colSize.x = 206.0f;
	_colSize.y = 175.0f;
	_spd = 8;
	auto juge = static_cast<int>(utility::get_random( 0,1 ));
	if ( juge % 2 == 0 )
	{
		isRight = true;
	}
	else
	{
		isRight = false;
	}

}

bool TitlePlayer::Update( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Update( game,mode );
	// キー入力を判定して、主人公を移動させる
	// Vector2を利用して斜め移動でも問題ないように
	Vector2 dir = {game.Getinput().GetLstickX(),-(game.Getinput().GetLstickY())};		// 方向を指定

	if ( dir.x != 0 || dir.y != 0 )
	{
		dir.Normalized();	// 方向をノーマライズ
	}

	if ( dir.x > 0.f )
	{
		isRight = true;
	}
	if ( dir.x < 0.f )
	{
		isRight = false;
	}
	dir *= _spd;		// ノーマライズした方向に速度をかける
	_pos += dir;		// 位置を動かす  

	// 画面の外に出ないようにする
	if ( _pos.x < 0 )
	{
		_pos.x = 0;
	}
	if ( _pos.x + _size.x > game.DispSizeW() )
	{
		_pos.x = game.DispSizeW() - _size.x;
	}
	if ( _pos.y < 0 )
	{
		_pos.y = 0;
	}
	if ( _pos.y + _size.y > game.DispSizeH() )
	{
		_pos.y = game.DispSizeH() - _size.y;
	}

	UpdateCollision();	// コリジョン更新
	return true;
}


bool TitlePlayer::Draw( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Draw( game,mode );
	if ( !isRight )
	{
		DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	}
	if ( isRight )
	{
		DrawTurnGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	}
	DrawCollision();	// コリジョン描画
	return true;
}

