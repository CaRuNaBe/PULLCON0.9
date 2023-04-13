#pragma once
#include "EffectBase.h"
class EffectDeathObject :public EffectBase
{
public:
	EffectDeathObject(ApplicationBase& game, int layer, ModeMainGame& mode);
	virtual ~EffectDeathObject();

	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();
};

