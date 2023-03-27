#pragma once
#include "UIBase.h"
class UIBase;
class UITutorial :public UIBase {
public:
	UITutorial(ApplicationBase& game, int layer, ModeMainGame& _base);
	virtual ~UITutorial();

	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
private:
	int handle_tutorial_A;
	int handle_tutorial_B;
	int handle_tutorial_X;
	int handle_tutorial_R2;
};
