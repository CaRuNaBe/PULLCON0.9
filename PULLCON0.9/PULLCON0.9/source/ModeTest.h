#pragma once
#include "appframe.h"
#include "ui/BaseUI.h"
class ModeTest: public ModeBase
{
public:
	ModeTest( ApplicationBase& game,int layer );
	virtual ~ModeTest();
	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();

private:
	GameServer<BaseUI> ui_player;
};


