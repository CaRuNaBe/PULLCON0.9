#pragma once
#include "appframe.h"
#include "EffectBase.h"
class EffectDestroyAmmo : public EffectBase
{
public:
	EffectDestroyAmmo(ApplicationBase& game, int layer, ModeMainGame& mode);
	virtual ~EffectDestroyAmmo();

	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();
};

