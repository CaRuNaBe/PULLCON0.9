#include "StartLogo.h"
#include "Dxlib.h"
StartLogo::StartLogo( ApplicationBase& game,ModeTitle& mode )
	: ActorBase2d( game,mode )
{
	_cg = ResourceServer::LoadGraph( "res/title/ui_Title_StartLogo.png" );

	Init();
}

StartLogo::~StartLogo()
{
}

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

bool StartLogo::Update()
{
	ActorBase2d::Update();
	for ( auto&& obje : _mode.Get2DobjectServer().GetObjects() )
	{
		if ( (obje->GetType() == ActorBase2d::Type::KPLAYER) )
		{
			if ( IsHitObject( *obje ) )
			{
				if ( _game.Getinput().GetTrgXinput( XINPUT_BUTTON_X ) )
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


bool StartLogo::Draw()
{
	ActorBase2d::Draw();
	DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	DrawCollision();	// �R���W�����`��
	return true;
}


