#include "Dxlib.h"
#include "TitlePlayer.h"


TitlePlayer::TitlePlayer()
	: ActorBase2d()
{
	_cg = ResourceServer::LoadGraph("res/title/ヘリ_タイトル.png");

	Init();
}

TitlePlayer::~TitlePlayer()
{}

void TitlePlayer::Init()
{
	ActorBase2d::Init();

	// プレイヤー情報の初期化
	_size.x = 48;
	_size.y = 48;
	_colPos.x = 8;
	_colPos.y = 8;
	_colSize.x = 32;
	_colSize.y = 32;
	_pos.x = static_cast<float>(utility::get_random(0,1920));
	_pos.y = static_cast<float>(utility::get_random(0,1000));
	_spd = 8;

}

bool TitlePlayer::Update(ApplicationBase& game)
{
	ActorBase2d::Update(game);


	// キー入力を判定して、主人公を移動させる
	// Vector2を利用して斜め移動でも問題ないように
	Vector2 dir = {game.Getinput().GetLstickX(),-(game.Getinput().GetLstickY())};		// 方向を指定

	if(dir.x != 0 || dir.y != 0)
	{
		dir.Normalize();	// 方向をノーマライズ
	}
	dir *= _spd;		// ノーマライズした方向に速度をかける
	_pos += dir;		// 位置を動かす  
	// 画面の外に出ないようにする
	if(_pos.x < 0)
	{
		_pos.x = 0;
	}
	if(_pos.x + _size.x > game.DispSizeW())
	{
		_pos.x = game.DispSizeW() - _size.x;
	}
	if(_pos.y < 0)
	{
		_pos.y = 0;
	}
	if(_pos.y + _size.y > game.DispSizeH())
	{
		_pos.y = game.DispSizeH() - _size.y;
	}



	UpdateCollision();	// コリジョン更新
	return true;
}


bool TitlePlayer::Draw(ApplicationBase& game)
{
	ActorBase2d::Draw(game);

	DrawGraph(static_cast<int>(_pos.x),static_cast<int>(_pos.y),_cg,TRUE);

	DrawCollision();	// コリジョン描画
	return true;
}

