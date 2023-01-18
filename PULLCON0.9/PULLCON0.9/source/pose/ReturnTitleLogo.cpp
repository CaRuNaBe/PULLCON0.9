#include "ReturnTitleLogo.h"
ReturnTitleLogo::ReturnTitleLogo(): ActorBase2d()
{
	Init();
}

ReturnTitleLogo::~ReturnTitleLogo()
{    // �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle( FontHandle );
}

void ReturnTitleLogo::Init()
{
	ActorBase2d::Init();

	_pos = {0.0f,157.0f};
	_size = {166.0f,86.0f};
	_colPos = {0.0f,0.0f};
	_colSize = {166.0f,86.0f};
	_spd = 0;
			// �@�f�t�H���g�̃t�H���g�ŁA�T�C�Y�S�O�A�����R�̃t�H���g���쐬��
	// �쐬�����f�[�^�̎��ʔԍ���ϐ� FontHandle �ɕۑ�����
	FontHandle = CreateFontToHandle( NULL,32,3 );
}

bool ReturnTitleLogo::Update( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Update( game,mode );
	UpdateCollision();	// �R���W�����X�V
	return true;
}


bool ReturnTitleLogo::Draw( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Draw( game,mode );
	DrawStringToHandle( _pos.IntX(),_pos.IntY(),"�^�C�g���ɖ߂�",GetColor( 0,255,0 ),FontHandle );
	DrawCollision();	// �R���W�����`��
	return true;
}
