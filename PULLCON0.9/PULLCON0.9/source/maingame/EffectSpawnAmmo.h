#pragma once
#include "EffectBase.h"
class EffectSpawnAmmo:public EffectBase
{
public:
	EffectSpawnAmmo( ApplicationBase& game,ModeMainGame& mode );
	virtual ~EffectSpawnAmmo();

	virtual void Init();
	virtual bool Update();
	virtual bool Draw();
private:
};

