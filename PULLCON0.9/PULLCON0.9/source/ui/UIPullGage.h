#pragma once
#include "UIBase.h"
#include "appframe.h"
class UIPullGage:public UIBase
{
	enum class State
	{
	
	};
public:
	UIPullGage( ApplicationBase& game,int layer,ModeBase& _base );
	virtual ~UIPullGage();

	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
	virtual bool DebugDraw();
private:

	int handle_do_pullout;
	int handle_meter_body;
	int handle_dopulloutmeter_xbutton_on;
	int handle_dopulloutmeter_xbutton_off;
	int hamdle_dopulloutmeterbutton_off;
	int handle_dopulloutmeterbutton_on;
	int handle_dopulloutmeterbutton_triangle;
};

