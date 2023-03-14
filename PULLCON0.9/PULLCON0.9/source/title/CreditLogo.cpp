#include "CreditLogo.h"
#include "Dxlib.h"
CreditLogo::CreditLogo( ApplicationBase& game,int layer,ModeTitle& mode )
	: ActorTitle( game,layer,mode )
{
	_cg = ResourceServer::LoadGraph( "res/2D_image/title/ui_Title_CreditLogo.png" );

	Init();
}

CreditLogo::~CreditLogo()
{}

void CreditLogo::Init()
{
	ActorTitle::Initialize();
	_pos = {900.0f,900.0f};
	_size = {156.0f,466.0f};
	_colPos = {0.0f,0.0f};
	_colSize = {156.0f,466.0f};
	_spd = 0;
}

bool CreditLogo::Update()
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


bool CreditLogo::Draw()
{
	ActorTitle::Draw();
	DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	DrawCollision();	// コリジョン描画
	return true;
}