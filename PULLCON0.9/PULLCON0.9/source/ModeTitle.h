#pragma once
#include "appframe.h"
class ModeTitle:public ModeBase
{
	typedef ModeBase base;
public:
	ModeTitle(ApplicationBase& game,int layer);
	virtual ~ModeTitle();
	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
private:

};