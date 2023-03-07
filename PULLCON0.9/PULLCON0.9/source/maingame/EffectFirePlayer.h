#pragma once
#include "EffectBase.h"
class EffectFirePlayer: public EffectBase
{
public:
	EffectFirePlayer( ApplicationBase& game,ModeMainGame& mode );
	virtual ~EffectFirePlayer();

	virtual void Init();
	virtual bool Update();
	virtual bool Draw();
};

