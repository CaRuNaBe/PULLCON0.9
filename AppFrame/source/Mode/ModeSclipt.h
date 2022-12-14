#pragma once
#include "ModeBase.h"
#include"string"
#include "../scliptengin/script_engine.h"

class ModeSclipt:public ModeBase
{
public:
	ModeSclipt(ApplicationBase& game,int layer,std::string storyname);
	virtual ~ModeSclipt();

	virtual bool Update();  // çXêV
	virtual bool Draw();	// ï`âÊ

private:
	ScriptEngine script;
};
