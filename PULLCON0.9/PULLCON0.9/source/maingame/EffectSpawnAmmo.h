#pragma once
#include "EffectBase.h"
class EffectSpawnAmmo:public EffectBase
{
public:
	EffectSpawnAmmo( ApplicationBase& game, int layer, ModeMainGame& mode );
	virtual ~EffectSpawnAmmo();

	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();
private:
};

