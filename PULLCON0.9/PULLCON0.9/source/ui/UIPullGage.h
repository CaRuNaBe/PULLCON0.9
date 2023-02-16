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
	std::array<int,7 > hundle_pullgage;
	int brack;
	bool is_hide;
};

