#pragma once
#include "EffectBase.h"
class EffectFireGunship:public EffectBase
{
public:
	EffectFireGunship( ApplicationBase& game, int layer, ModeMainGame& mode );
	virtual ~EffectFireGunship();

	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();
};

