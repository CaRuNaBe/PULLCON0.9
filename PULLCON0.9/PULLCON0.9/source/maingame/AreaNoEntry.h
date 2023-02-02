#pragma once
#include "appframe.h"

class AreaNoEntry:
	public ActorBase3D
{
	using base = ActorBase3D;
public:
	AreaNoEntry( ApplicationBase& game,ModeBase& mode , float _radius,float _height );
	virtual ~AreaNoEntry();
	virtual Type GetType()
	{
		return Type::kAreaNoEntry;
	}
	virtual void Init();
	virtual bool Update();
	virtual bool Draw( );

protected:
	float  height;
	float radius;
};

