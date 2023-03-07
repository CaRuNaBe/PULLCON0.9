#pragma once
#include "EffectBase.h"
class EffectDefeatEnemy:public EffectBase
{
public:
	EffectDefeatEnemy( ApplicationBase& game,ModeMainGame& mode );
	virtual ~EffectDefeatEnemy();

	virtual void Init();
	virtual bool Update();
	virtual bool Draw();
};

