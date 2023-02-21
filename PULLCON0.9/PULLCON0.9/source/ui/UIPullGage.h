#pragma once
#include "UIBase.h"
#include "appframe.h"
#include <array>
#include "../maingame/Player.h"
#include <memory>
class UIPullGage:public UIBase
{
	enum class State
	{

	};
public:
	UIPullGage( ApplicationBase& game,int layer,ModeBase& _base );
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

