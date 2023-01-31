#pragma once
#include "appframe.h"
class SupplyEria:
    public ActorBase3D
{
	using base = ActorBase3D;
public:
	SupplyEria( ApplicationBase& game,ModeBase& mode , float _radius );
	virtual ~SupplyEria();
	virtual Type GetType()
	{
		return Type::kSupplyEria;
	}
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

protected:
	int    _handle;
	float radius;
};

