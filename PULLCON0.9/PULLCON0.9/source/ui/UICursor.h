#pragma once
#include "../maingame/Player.h"
#include "UIBase.h"
class UIBase;
class UICursor:public UIBase
{
public:
	UICursor( ApplicationBase& game,int layer,ModeMainGame& _base );
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

