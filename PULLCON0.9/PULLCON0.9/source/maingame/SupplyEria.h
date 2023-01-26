#pragma once
#include "appframe.h"
class SupplyEria:
    public ActorBase3D
{
	using base = ActorBase3D;
public:
	SupplyEria( float _radius );
	virtual ~SupplyEria();
	virtual Type GetType()
	{
		return Type::kSupplyEria;
	}
	virtual void Init();
	virtual bool Update( ApplicationBase& game,ModeBase& mode );
	virtual bool Draw( ApplicationBase& game,ModeBase& mode );

protected:
	int    _handle;
	int radius;
};

