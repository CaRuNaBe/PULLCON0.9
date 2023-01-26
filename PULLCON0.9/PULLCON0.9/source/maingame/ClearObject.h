#pragma once
#include "appframe.h"
class ClearObject:
    public ActorBase3D
{
	using base = ActorBase3D;
public:
	ClearObject( float _radius );
	virtual ~ClearObject();
	virtual Type GetType()
	{
		return Type::kClearObject;
	}
	virtual void Init();
	virtual bool Update( ApplicationBase& game,ModeBase& mode );
	virtual bool Draw( ApplicationBase& game,ModeBase& mode );

	virtual void Damage(ModeBase& mode);

protected:
	vector4 _vObjective;

	int    _handle;
	float radius;
};

