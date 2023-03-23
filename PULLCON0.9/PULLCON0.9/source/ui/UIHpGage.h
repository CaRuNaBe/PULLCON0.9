#pragma once
#include "appframe.h"
#include "UIBase.h"
class UIBase;
class UIHpGage:public UIBase
{
public:
	UIHpGage( ApplicationBase& game,int layer,ModeMainGame& _base );
	virtual ~UIHpGage();

	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
	virtual bool DebugDraw();
private:
	int handle_hp_body;
	int handle_hp_gage;
	int handle_hp_alert;
	float hp_gage_now_posi;
	bool is_alert;
};

