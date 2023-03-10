#pragma once
#include "EffectBase.h"
class EffectFireGunship:public EffectBase
{
public:
	EffectFireGunship( ApplicationBase& game,ModeMainGame& mode );
	virtual ~EffectFireGunship();

	virtual void Init();
	virtual bool Update();
	virtual bool Draw();
};

