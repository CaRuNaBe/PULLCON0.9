#pragma once
//#include"../GameScenario/GameScriptEngine.h"
#include "appframe.h"
#include<vector>
#include<memory>
#include<string>

class ApplicationMain;

class ModeMainGame:public ModeBase
{
public:
	ModeMainGame( ApplicationMain& game ,int layer,std::string stagename);
	virtual ~ModeMainGame();
	void Init ();

	virtual bool Update ( ); // �X�V

	virtual bool Draw ( );	// �`��
protected:
	//GameScriptEngine GameSclipt;
};
