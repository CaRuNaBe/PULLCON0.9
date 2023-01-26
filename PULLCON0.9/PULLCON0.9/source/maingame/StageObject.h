#pragma once
#include "appframe.h"

class StageObject:
    public ActorBase3D
{
	using base = ActorBase3D;
public:
	StageObject( int objectid,int collision );
	virtual ~StageObject();
	virtual Type GetType()
	{
		return Type::kStageObject;
	}
	virtual void Init();
	virtual bool Update( ApplicationBase& game,ModeBase& mode );
	virtual bool Draw( ApplicationBase& game,ModeBase& mode );

protected:
	int    _handle;
	bool is_coll;
};

