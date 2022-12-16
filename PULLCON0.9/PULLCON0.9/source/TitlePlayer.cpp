#include "Dxlib.h"
#include "TitlePlayer.h"


TitlePlayer::TitlePlayer()
	: ActorBase2d()
{
	_cg = ResourceServer::LoadGraph("res/title/�w��_�^�C�g��.png");

	Init();
}

TitlePlayer::~TitlePlayer()
{}

void TitlePlayer::Init()
{
	ActorBase2d::Init();

	// �v���C���[���̏�����
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


	// �L�[���͂𔻒肵�āA��l�����ړ�������
	// Vector2�𗘗p���Ď΂߈ړ��ł����Ȃ��悤��
	Vector2 dir = {game.Getinput().GetLstickX(),-(game.Getinput().GetLstickY())};		// �������w��

	if(dir.x != 0 || dir.y != 0)
	{
		dir.Normalize();	// �������m�[�}���C�Y
	}
	dir *= _spd;		// �m�[�}���C�Y���������ɑ��x��������
	_pos += dir;		// �ʒu�𓮂���  
	// ��ʂ̊O�ɏo�Ȃ��悤�ɂ���
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



	UpdateCollision();	// �R���W�����X�V
	return true;
}


bool TitlePlayer::Draw(ApplicationBase& game)
{
	ActorBase2d::Draw(game);

	DrawGraph(static_cast<int>(_pos.x),static_cast<int>(_pos.y),_cg,TRUE);

	DrawCollision();	// �R���W�����`��
	return true;
}

