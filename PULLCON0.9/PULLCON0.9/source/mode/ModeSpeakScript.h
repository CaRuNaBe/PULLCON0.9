#pragma once
#include "appframe.h"
#include"string"

class ModeSpeakScript:public ModeBase
{
public:
	ModeSpeakScript(ApplicationBase& game,int layer,std::string storyname);
	virtual ~ModeSpeakScript();

	virtual bool Update();  // çXêV
	virtual bool Draw();	// ï`âÊ

private:
	int Tem_image;
	int timer;
	std::string story_name;
};
