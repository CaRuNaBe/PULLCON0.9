#pragma once
#include "UIBase.h"
#include "appframe.h"
class UIFuelGage:public UIBase
{
public:
	UIFuelGage( ApplicationBase& game,int layer,ModeBase& _base );
	virtual ~UIFuelGage();

	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
	virtual bool DebugDraw();
private:
	int handle_fuel_body;
	int handle_fuel_gage;
	float fuel_gage_now_posi;
};

