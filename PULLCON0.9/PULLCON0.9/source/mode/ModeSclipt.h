#pragma once
#include "appframe.h"
#include"string"

class ModeSclipt:public ModeBase
{
public:
	ModeSclipt(ApplicationBase& game,int layer,std::string storyname);
	virtual ~ModeSclipt();

	virtual bool Update();  // �X�V
	virtual bool Draw();	// �`��

private:
};
