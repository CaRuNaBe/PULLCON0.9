#pragma once
#include "BaseUI.h"
#include "appframe.h"
class UIFuelGage:public BaseUI
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

