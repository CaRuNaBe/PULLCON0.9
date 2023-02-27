
#pragma once
#include "appframe.h"
class ModeResourceRoad:public GameBase
{
	using base = GameBase;
public:
	ModeResourceRoad( ApplicationBase& game,int layer );
	virtual ~ModeResourceRoad();
	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
	virtual bool DebugDraw();
private:
};

