#pragma once
#include "UIBase.h"
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
	math::vector4  posi_cursor;
};

