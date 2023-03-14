#include "EndLogo.h"
#include "Dxlib.h"
EndLogo::EndLogo( ApplicationBase& game,int layer,ModeTitle& mode )
	: ActorTitle( game,layer,mode )
{
	_cg = ResourceServer::LoadGraph( "res/2D_image/title/ui_Title_EndLogo.png" );

	Initialize();
}

EndLogo::~EndLogo()
{
}

void EndLogo::Initialize()
{
	ActorTitle::Initialize();
	_pos.x = 1350.0f;
	_pos.y = 900.0f;
	_size.x = 156.0f;
	_size.y = 466.0f;
	_colPos.x = 0.0f;
	_colPos.y = 0.0f;
	_colSize.x = 156.0f;
	_colSize.y = 466.0f;
	_spd = 0;
}

bool EndLogo::Update()
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
					_spd = static_cast<float>(math::utility::get_random( 5,20 ));
					_pos.y -= _spd;		// 位置を動かす  
				}
			}
		}
	}
	UpdateCollision();	// コリジョン更新
	return true;
}


bool EndLogo::Draw()
{
	ActorTitle::Draw();
	DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	DrawCollision();	// コリジョン描画
	return true;
}