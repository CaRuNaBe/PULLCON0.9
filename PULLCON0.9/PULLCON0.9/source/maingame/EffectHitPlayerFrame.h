#pragma once
#include "EffectBase.h"
class EffectHitPlayerFrame:public EffectBase
{
public:
	EffectHitPlayerFrame( ApplicationBase& game, int layer, ModeMainGame& mode );
	virtual ~EffectHitPlayerFrame();

	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();
};

