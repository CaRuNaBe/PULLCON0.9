#pragma once
#include "appframe.h"
class BaseUI:public GameBase
{
public:
	BaseUI( ApplicationBase& game,int layer,ModeBase& _base );
	virtual ~BaseUI();

	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
	virtual bool DebugDraw();
protected:
	ModeBase& mode_base;
};

