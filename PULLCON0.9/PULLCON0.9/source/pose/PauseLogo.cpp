#include "PauseLogo.h"
PauseLogo::PauseLogo( ApplicationBase& game,ModeBase& mode ): ActorBase2d( game,mode )
{
	Init();
}

PauseLogo::~PauseLogo()
{    // �쐬�����t�H���g�f�[�^���폜����
	DeleteFontToHandle( FontHandle );
}

void PauseLogo::Init()
{
	ActorBase2d::Init();

	_pos = {0.0f,0.0f};
	_size = {166.0f,86.0f};
	_colPos = {0.0f,0.0f};
	_colSize = {166.0f,86.0f};
	_spd = 0;
			// �f�t�H���g�̃t�H���g�ŁA�T�C�Y�S�O�A�����R�̃t�H���g���쐬��
	// �쐬�����f�[�^�̎��ʔԍ���ϐ� FontHandle �ɕۑ�����
	FontHandle = CreateFontToHandle( NULL,128,3 );
}

bool PauseLogo::Update()
{
	ActorBase2d::Update();
	//ChangeFontType( �t�H���g�^�C�v );
	UpdateCollision();	// �R���W�����X�V
	return true;
}


bool PauseLogo::Draw()
{
	ActorBase2d::Draw();
	DrawStringToHandle( _pos.IntX(),_pos.IntY(),"Pause",GetColor( 0,255,0 ),FontHandle );
	DrawCollision();	// �R���W�����`��
	return true;
}
