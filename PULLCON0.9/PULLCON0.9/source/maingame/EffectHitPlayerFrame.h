#pragma once
#include "EffectBase.h"
class EffectHitPlayerFrame:public EffectBase
{
public:
	EffectHitPlayerFrame( ApplicationBase& game,ModeMainGame& mode );
	virtual ~EffectHitPlayerFrame();

	virtual void Init();
	virtual bool Update();
	virtual bool Draw();
};

