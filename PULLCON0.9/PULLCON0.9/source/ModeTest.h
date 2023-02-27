#pragma once
#include "appframe.h"
#include "mode/ModeMainGame.h"
#include "ui/UIBase.h"
#include "ui/UIHpGage.h"
#include "ui/UIFuelGage.h"
#include "ui/UICursor.h"
#include "ui/UIPullGage.h"
class ModeTest: public ModeMainGame
{
public:
	ModeTest( ApplicationBase& game,int layer );
	virtual ~ModeTest();
	virtual bool Initialize();
	virtual bool Update()override;
	virtual bool Draw()override;

private:


};


