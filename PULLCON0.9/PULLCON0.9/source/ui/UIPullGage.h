#pragma once
#include "appframe.h"
#include <array>
#include "../maingame/Player.h"
#include <memory>
#include "UIBase.h"
class UIBase;
class UIPullGage:public UIBase
{
public:
	UIPullGage( ApplicationBase& game,int layer,ModeMainGame& _base );
	virtual ~UIPullGage();

	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
	virtual bool DebugDraw();
private:
	std::array<int,5 > hundle_pullgage;
	std::array<int,2 > hundle_xbutton;
	int brack;
	bool is_hide;
	bool is_pullok;
	int player_pull_now_count;
	int button_on_count;
};

