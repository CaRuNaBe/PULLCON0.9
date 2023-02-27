#pragma once
#include "appframe.h"
#include "../mode/ModeMainGame.h"
class UIBase:public GameBase
{
public:
	UIBase( ApplicationBase& game,int layer,ModeMainGame& _base );
	virtual ~UIBase();

	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
	virtual bool DebugDraw();
protected:
	ModeMainGame& mode_base;
};

