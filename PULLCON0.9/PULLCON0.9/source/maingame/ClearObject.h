#pragma once
#include "appframe.h"
class ClearObject:
    public ActorBase3D
{
	using base = ActorBase3D;
public:
	ClearObject();
	virtual ~ClearObject();
	virtual Type GetType()
	{
		return Type::kClearObject;
	}
	virtual void Init();
	virtual bool Update( ApplicationBase& game,ModeBase& mode );
	virtual bool Draw( ApplicationBase& game,ModeBase& mode );

protected:
	int    _handle;
};

