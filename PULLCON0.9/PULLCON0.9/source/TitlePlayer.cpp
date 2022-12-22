#include "Dxlib.h"
#include "TitlePlayer.h"


TitlePlayer::TitlePlayer()
	: ActorBase2d()
{
	cg_player = ResourceServer::LoadGraph( "res/title/cg_Heli.png" );
	cg_ui = ResourceServer::LoadGraph( "res/title/ui_Push_Guide.png" );
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
	_colSize.y = 160.0f;
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
	isUidraw = false;
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
	for ( auto&& obje : mode.Get2DobjectServer().GetObjects() )
	{
		if ( (obje->GetType() == ActorBase2d::Type::KGAMESTARTLOGO) || (obje->GetType() == ActorBase2d::Type::KCREDITLOGO) || (obje->GetType() == ActorBase2d::Type::KENDLOGO) )
		{
			isUidraw = true;
			if ( IsHitObject( *obje ) )
			{
				
				/*
				if ( !isRight )
				{
					if ( game.Getinput().GetKeyXinput( XINPUT_BUTTON_A ) )
					{
					}
				}
				if ( isRight )
				{
					if ( game.Getinput().GetKeyXinput( XINPUT_BUTTON_A ) )
					{
					}
				}
				*/
			}
			else
			{
				isUidraw = false;
			}
		}
	}
	UpdateCollision();	// コリジョン更新
	return true;
}


bool TitlePlayer::Draw( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Draw( game,mode );
	if ( !isRight )
	{
		DrawGraph( _pos.IntX(),_pos.IntY(),cg_player,TRUE );
	}
	else
	{
		DrawTurnGraph( _pos.IntX(),_pos.IntY(),cg_player,TRUE );
	}
	if ( isUidraw )
	{
		const Vector2 uisize = {150,150};
		Vector2 uiposi = {(_pos.x)-(uisize.x),_pos.y};
		
		if ( uiposi.x < 0.0f)
		{
			uiposi.x = 0.0f;
		}
		if ( uiposi.x + uisize.x > game.DispSizeW() )
		{
			uiposi.x = static_cast <float>(game.DispSizeW()) - uiposi.x;
		}
		if ( uiposi.y < 0.0f )
		{
			uiposi.y = 0.0f;
		}
		if ( uiposi.y + uisize.y > static_cast <float>(game.DispSizeH()) )
		{
			uiposi.y = game.DispSizeH() - uisize.y;
		}
		DrawTurnGraph( uiposi.IntX(),uiposi.IntY(),cg_ui,TRUE );
	}

#if _DEBUG
	int x = 0,y = 0,size = 16;
	SetFontSize( size );
	//DrawFormatString( x,y,GetColor( 255,0,0 ),"Camera:" ); y += size;
	//DrawFormatString( x,y,GetColor( 255,0,0 ),"  target = (%5.2f, %5.2f, %5.2f)",_cam._vTarget.x,_cam._vTarget.y,_cam._vTarget.z ); y += size;
	DrawFormatString( x,y,GetColor( 255,0,0 ),"  pos    = (%5.2f, %5.2f)",_pos.x,_pos.y ); y += size;
#endif
	DrawCollision();	// コリジョン描画
	return true;
}

