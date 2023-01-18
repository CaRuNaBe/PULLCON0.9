#include "StartLogo.h"
#include "Dxlib.h"
StartLogo::StartLogo()
	: ActorBase2d()
{
	_cg = ResourceServer::LoadGraph( "res/title/ui_Title_StartLogo.png" );

	Init();
}

StartLogo::~StartLogo()
{}

void StartLogo::Init()
{
	ActorBase2d::Init();

	// �v���C���[���̏�����
	_pos = {450.0f,900.0f};
	_size = {156.0f,466.0f};
	_colPos = {0.0f,0.0f};
	_colSize = {156.0f,466.0f};
	_spd = 0;
}

bool StartLogo::Update( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Update( game,mode );
	for ( auto&& obje : mode.Get2DobjectServer().GetObjects() )
	{
		if ( (obje->GetType() == ActorBase2d::Type::KPLAYER) )
		{
			if ( IsHitObject( *obje ) )
			{
				if ( game.Getinput().GetTrgXinput( XINPUT_BUTTON_X ) )
				{
					_spd = static_cast<float>(utility::get_random( 5,20 ));
					_pos.y -= _spd;		// �ʒu�𓮂���  
				}
			}
		}
	}

	UpdateCollision();	// �R���W�����X�V
	return true;
}


bool StartLogo::Draw( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Draw( game,mode );
	DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	DrawCollision();	// �R���W�����`��
	return true;
}


