#pragma once
#include "EffectBase.h"
class EffectFirePlayer: public EffectBase
{
public:
	EffectFirePlayer( ApplicationBase& game, int layer, ModeMainGame& mode );
	virtual ~EffectFirePlayer();

	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();
};

