#pragma once
#include "ModeBase.h"
#include"string"
#include "../scliptengin/script_engine.h"

class ModeSclipt:public ModeBase
{
public:
	ModeSclipt(ApplicationBase& game,int layer,std::string storyname);
	virtual ~ModeSclipt();

	virtual bool Update();  // �X�V
	virtual bool Draw();	// �`��

private:
	ScriptEngine script;
};
