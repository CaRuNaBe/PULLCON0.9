#pragma once
#include "dxlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<memory>
#include "../Mode/ModeServer.h"
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
	//ゲームモード管理クラス取得
	std::shared_ptr<ModeServer> GetModeServer()
	{
		return _serverMode;
	}

	//入力取得
	InputManager& Getinput()
	{
		return _input;
	}
	int& GetFontHandle()
	{
		return font_hundle;
	}
	int GetFuntSize()
	{
		return font_size;
	}
protected:
	static	ApplicationBase* _lpInstance;

	std::shared_ptr<ModeServer> _serverMode;//
	InputManager _input;//inputクラスインスタス
	int font_hundle;
	int font_size;
};
