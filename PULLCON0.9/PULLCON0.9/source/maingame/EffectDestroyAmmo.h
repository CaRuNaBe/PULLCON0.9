#pragma once
#include "appframe.h"
#include "EffectBase.h"
class EffectDestroyAmmo: public EffectBase
{
public:
	EffectDestroyAmmo( ApplicationBase& game,ModeMainGame& mode );
	virtual ~EffectDestroyAmmo();

	virtual void Init();
	virtual bool Update();
	virtual bool Draw();
};

