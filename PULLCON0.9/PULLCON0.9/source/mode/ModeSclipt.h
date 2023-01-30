#pragma once
#include "appframe.h"
#include"string"

class ModeSclipt:public ModeBase
{
public:
	ModeSclipt(ApplicationBase& game,int layer,std::string storyname);
	virtual ~ModeSclipt();

	virtual bool Update();  // çXêV
	virtual bool Draw();	// ï`âÊ

private:
};
