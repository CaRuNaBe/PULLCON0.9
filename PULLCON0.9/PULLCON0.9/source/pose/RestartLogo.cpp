#include "RestartLogo.h"
RestartLogo::RestartLogo(): ActorBase2d()
{
	Init();
}

RestartLogo::~RestartLogo()
{    // �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle( FontHandle );
}

void RestartLogo::Init()
{
	ActorBase2d::Init();

	_pos = {0.0f,128.0f};
	_size = {166.0f,86.0f};
	_colPos = {0.0f,0.0f};
	_colSize = {166.0f,86.0f};
	_spd = 0;
	// �쐬�����f�[�^�̎��ʔԍ���ϐ� FontHandle �ɕۑ�����
	FontHandle = CreateFontToHandle( NULL,32,3 );
}

bool RestartLogo::Update( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Update( game,mode );
	UpdateCollision();	// �R���W�����X�V
	return true;
}


bool RestartLogo::Draw( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Draw( game,mode );
	DrawStringToHandle( _pos.IntX(),_pos.IntY(),"�Q�[�����ĊJ����",GetColor( 0,255,0 ),FontHandle );
	DrawCollision();	// �R���W�����`��
	return true;
}
