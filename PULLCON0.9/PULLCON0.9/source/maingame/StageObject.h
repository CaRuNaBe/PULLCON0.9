#pragma once
#include "appframe.h"

class StageObject:
    public ActorBase3D
{
	using base = ActorBase3D;
public:
	StageObject( ApplicationBase& game,ModeBase& mode,int objectid,int collision );
	virtual ~StageObject();
	virtual Type GetType()
	{
		return Type::kStageObject;
	}

	virtual void Init();
	virtual bool Update(  );
	virtual bool Draw( );

protected:
	int    _handle;
};

