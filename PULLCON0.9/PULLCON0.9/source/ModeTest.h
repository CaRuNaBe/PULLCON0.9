#pragma once
#include "appframe.h"
#include "ui/UIBase.h"
#include "ui/UIHpGage.h"
#include "ui/UIFuelGage.h"
#include "ui/UICursor.h"
#include "ui/UIPullGage.h"
class ModeTest: public ModeBase
{
public:
	ModeTest( ApplicationBase& game,int layer );
	virtual ~ModeTest();
	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();

private:
	GameServer<UIBase> ui_player;

};


