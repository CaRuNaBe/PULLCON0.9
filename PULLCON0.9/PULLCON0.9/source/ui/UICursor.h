#pragma once
#include "UIBase.h"
#include "../maingame/Player.h"
class UICursor:public UIBase
{
public:
	UICursor( ApplicationBase& game,int layer,ModeBase& _base );
	virtual ~UICursor();

	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
	virtual bool DebugDraw();
private:
	int handle_cursor;
	bool is_hide;
	math::vector4  posi_cursor;
};

