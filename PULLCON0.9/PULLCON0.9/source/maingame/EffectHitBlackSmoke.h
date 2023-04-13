#pragma once
#include "EffectBase.h"
class EffectHitBlackSmoke:public EffectBase
{
public:
	EffectHitBlackSmoke( ApplicationBase& game, int layer, ModeMainGame& mode );
	virtual ~EffectHitBlackSmoke();

	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();
};

