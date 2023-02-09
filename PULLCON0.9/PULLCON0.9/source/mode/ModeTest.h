#pragma once
#include "appframe.h"
using namespace math;

class ModeTest : public ModeBase
{
	typedef ModeBase base;
public:
	ModeTest(ApplicationBase& game,int layer);
	virtual ~ModeTest();
	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();


public:



}; 


