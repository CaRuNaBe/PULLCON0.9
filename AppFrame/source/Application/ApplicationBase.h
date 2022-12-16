#pragma once
#include "dxlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<memory>
#include "../Mode/ModeServer.h"
#include "ScliptFlagManager.h"
#include "../Object/ObjectServer.h"
#include"input_manager.h"



class ApplicationBase
{
public:
	ApplicationBase();
	virtual ~ApplicationBase();

	virtual bool Initialize(HINSTANCE hInstance);
	virtual bool Terminate();
	virtual bool Input();
	virtual bool Update();
	virtual bool Draw();

	virtual bool AppWindowed()
	{
		return true;
	}
	virtual int DispSizeW()
	{
		return 640;
	}
	virtual int DispSizeH()
	{
		return 480;
	}

	static	ApplicationBase* GetInstance()
	{
		return _lpInstance;
	}
	//�Q�[�����[�h�Ǘ��N���X�擾
	std::shared_ptr<ModeServer> GetModeServer()
	{
		return _serverMode;
	}
	//�t���O�}�l�[�W���[�擾
	std::shared_ptr<ScliptFlagManager> GetScliptFlagManager()
	{
		return _flagManager;
	}
	//���͎擾
	InputManager Getinput()
	{
		return _input;
	}
protected:
	static	ApplicationBase* _lpInstance;

	std::shared_ptr<ModeServer> _serverMode;//
	std::shared_ptr<ScliptFlagManager> _flagManager;//�t���O�}�l�[�W���[�|�C���^
	InputManager _input;//input�N���X�C���X�^�X
};
