
#include "ApplicationBase.h"

ApplicationBase	*ApplicationBase::_lpInstance = NULL;


ApplicationBase::ApplicationBase() {
	_lpInstance = this;
}

ApplicationBase::~ApplicationBase() {
}

bool ApplicationBase::Initialize(HINSTANCE hInstance) {

	// DX���C�u�����̏�����
	if(AppWindowed()){
		ChangeWindowMode(true);							// �E�B���h�E���[�h�Ɏw�肷��
	}
	SetGraphMode(DispSizeW(), DispSizeH(), 32);


	if (DxLib_Init() == -1)
	{	// �G���[���N�����璼���ɏI��
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// �`����ʂ𗠉�ʂɃZ�b�g


	// ���[�h�T�[�o�̏�����
	_serverMode = std::make_shared<ModeServer>(*this);
	_flagManager = std::make_shared<ScliptFlagManager>();
	return true;
}

bool ApplicationBase::Terminate() {

	// DX���C�u�����J��
	DxLib_End();

	return true;
}


bool ApplicationBase::Input() {
	_input.Update();
	return true;
}

bool ApplicationBase::Update() {
	_serverMode->UpdateInit();
	_serverMode->Update();
	_serverMode->UpdateFinish();
	return true;
}


bool ApplicationBase::Draw() {
	_serverMode->DrawInit();
	_serverMode->Draw();
	_serverMode->DrawFinish();
	return true;
}
