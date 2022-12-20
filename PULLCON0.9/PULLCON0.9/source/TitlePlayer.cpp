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

	// �v���C���[���̏�����
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
	// �L�[���͂𔻒肵�āA��l�����ړ�������
	// Vector2�𗘗p���Ď΂߈ړ��ł����Ȃ��悤��
	Vector2 dir = {game.Getinput().GetLstickX(),-(game.Getinput().GetLstickY())};		// �������w��

	if ( dir.x != 0 || dir.y != 0 )
	{
		dir.Normalized();	// �������m�[�}���C�Y
	}

	if ( dir.x > 0.f )
	{
		isRight = true;
	}
	if ( dir.x < 0.f )
	{
		isRight = false;
	}
	dir *= _spd;		// �m�[�}���C�Y���������ɑ��x��������
	_pos += dir;		// �ʒu�𓮂���  

	// ��ʂ̊O�ɏo�Ȃ��悤�ɂ���
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

	UpdateCollision();	// �R���W�����X�V
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
	DrawCollision();	// �R���W�����`��
	return true;
}

