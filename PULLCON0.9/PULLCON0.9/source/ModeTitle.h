#pragma once
#include<memory>
#include "appframe.h"
class ModeTitle:public ModeBase
{
	using base = ModeBase;
public:
	ModeTitle( ApplicationBase& game,int layer );
	virtual ~ModeTitle();
	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
private:

};