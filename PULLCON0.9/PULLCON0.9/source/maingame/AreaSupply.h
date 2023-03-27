#pragma once
#include "appframe.h"
#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
class AreaSupply :public ActorBase3D {
	using base = ActorBase3D;
public:
	AreaSupply(ApplicationBase& game, ModeMainGame& mode, float _radius);
	virtual ~AreaSupply();
	virtual Type GetType() { return Type::kAreaSupply; }
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

protected:
	int    _handle;
};

