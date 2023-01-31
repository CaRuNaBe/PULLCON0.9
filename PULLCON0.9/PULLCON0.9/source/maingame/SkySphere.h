#pragma once
#include "appframe.h"
class SkySphere:
    public ActorBase3D
{
	using base = ActorBase3D;
public:
	SkySphere( ApplicationBase& game,ModeBase& mode,int objectid);
	virtual ~SkySphere();
	virtual Type GetType()
	{
		return Type::kSkySphere;
	}
	virtual void Init();
	virtual bool Update(  );
	virtual bool Draw(  );

protected:
	int    _handle;
};

