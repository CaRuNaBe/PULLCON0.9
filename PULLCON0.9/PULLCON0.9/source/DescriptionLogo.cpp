#include "DescriptionLogo.h"
DescriptionLogo::DescriptionLogo(): ActorBase2d()
{
	Init();
}

DescriptionLogo::~DescriptionLogo()
{    // �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle( FontHandle );
}

void DescriptionLogo::Init()
{
	ActorBase2d::Init();

	_pos = {890.0f,850.0f};
	_size = {166.0f,86.0f};
	_colPos = {0.0f,0.0f};
	_colSize = {166.0f,86.0f};
	_spd = 0;
	// �쐬�����f�[�^�̎��ʔԍ���ϐ� FontHandle �ɕۑ�����
	FontHandle = CreateFontToHandle( NULL,32,3 );
}

bool DescriptionLogo::Update( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Update( game,mode );
	//ChangeFontType( �t�H���g�^�C�v );
	UpdateCollision();	// �R���W�����X�V
	return true;
}


bool DescriptionLogo::Draw( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Draw( game,mode );
	DrawStringToHandle( _pos.IntX(),_pos.IntY(),"�������",GetColor( 0,255,0 ),FontHandle );
	DrawCollision();	// �R���W�����`��
	return true;
}