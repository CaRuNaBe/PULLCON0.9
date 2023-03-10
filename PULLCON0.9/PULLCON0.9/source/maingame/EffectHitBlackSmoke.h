#pragma once
#include "EffectBase.h"
class EffectHitBlackSmoke:public EffectBase
{
public:
	EffectHitBlackSmoke( ApplicationBase& game,ModeMainGame& mode );
	virtual ~EffectHitBlackSmoke();

	virtual void Init();
	virtual bool Update();
	virtual bool Draw();
};

