#include "StartLogo.h"

#include "Dxlib.h"
StartLogo::StartLogo( ApplicationBase& game,int layer,ModeTitle& mode )
	: ActorTitle( game,layer,mode )
{
	_cg = ResourceServer::LoadGraph( "res/2D_image/title/ui_Title_StartLogo.png" );

	Initialize();
}

StartLogo::~StartLogo()
{}

void StartLogo::Initialize()
{
	ActorTitle::Initialize();

	// プレイヤー情報の初期化
	_pos = {450.0f,900.0f};
	_size = {156.0f,466.0f};
	_colPos = {0.0f,0.0f};
	_colSize = {156.0f,466.0f};
	_spd = 0;
}

bool StartLogo::Update()
{
	ActorTitle::Update();
	for ( auto&& obje : _mode.Get2DobjectServer().GetObjects() )
	{
		if ( (obje->GetType() == ActorTitle::Type::KPLAYER) )
		{
			if ( IsHitObject( *obje ) )
			{
				if ( _game.Getinput().GetTrgXinput( XINPUT_BUTTON_X ) )
				{
					_spd = static_cast<float>(math::utility::get_random( low_movement_pull,up_movement_pull ));
					_pos.y -= _spd;		// 位置を動かす  
					if ( _pos.y < 500 )
					{
						_pos.y = -1000;

					}
				}
			}
		}
	}

	UpdateCollision();	// コリジョン更新
	return true;
}


bool StartLogo::Draw()
{
	ActorTitle::Draw();
	DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	DrawCollision();	// コリジョン描画
	return true;
}


