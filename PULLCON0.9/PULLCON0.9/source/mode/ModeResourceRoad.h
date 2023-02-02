
#pragma once
#include "appframe.h"
class ModeResourceRoad :public ModeBase
{
	using base = ModeBase;
public:
	ModeResourceRoad( ApplicationBase& game,int layer );
	virtual ~ModeResourceRoad();
	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();

private:
};

