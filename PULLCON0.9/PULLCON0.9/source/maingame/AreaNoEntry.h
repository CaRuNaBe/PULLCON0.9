#pragma once
#include "appframe.h"

class AreaNoEntry:
	public ActorBase3D
{
	using base = ActorBase3D;
public:
	AreaNoEntry( int _radius,int _height );
	virtual ~AreaNoEntry();
	virtual Type GetType()
	{
		return Type::kAreaNoEntry;
	}
	virtual void Init();
	virtual bool Update( ApplicationBase& game,ModeBase& mode );
	virtual bool Draw( ApplicationBase& game,ModeBase& mode );

protected:
	int  height;
	int radius;
};

