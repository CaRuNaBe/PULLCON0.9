#pragma once
#include "appframe.h"
class SkySphere:
    public ActorBase3D
{
	using base = ActorBase3D;
public:
	SkySphere(int object_id);
	virtual ~SkySphere();
	virtual Type GetType()
	{
		return Type::kSkySphere;
	}
	virtual void Init();
	virtual bool Update( ApplicationBase& game,ModeBase& mode );
	virtual bool Draw( ApplicationBase& game,ModeBase& mode );

protected:
	int    _handle;
};

