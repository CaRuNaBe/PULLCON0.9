#pragma once
#include "appframe.h"
class UIBase:public GameBase
{
public:
	UIBase( ApplicationBase& game,int layer,ModeBase& _base );
	virtual ~UIBase();

	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
	virtual bool DebugDraw();
protected:
	ModeBase& mode_base;
};

