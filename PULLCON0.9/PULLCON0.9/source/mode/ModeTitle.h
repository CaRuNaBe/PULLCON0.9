#pragma once
#include<memory>
#include "appframe.h"
class ActorBase2d;
class ModeTitle:public ModeBase
{
	using base = ModeBase;
public:
	ModeTitle( ApplicationBase& game,int layer );
	virtual ~ModeTitle();
	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
	virtual bool DebugDraw();
private:
	
};