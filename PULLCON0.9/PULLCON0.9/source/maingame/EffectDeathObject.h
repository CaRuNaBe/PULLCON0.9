#pragma once
#include "EffectBase.h"
class EffectDeathObject:public EffectBase
{
public:
	EffectDeathObject( ApplicationBase& game,ModeMainGame& mode );
	virtual ~EffectDeathObject();

	virtual void Init();
	virtual bool Update();
	virtual bool Draw();
};

