#pragma once
#include "BaseUI.h"
#include "appframe.h"
class UIHpGage:public BaseUI
{
public:
	UIHpGage( ApplicationBase& game,int layer,ModeBase& _base );
	virtual ~UIHpGage();

	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
	virtual bool DebugDraw();
private:
	int handle_hp_body;
	int handle_hp_gage;
	float hp_gage_now_posi;
};

