#pragma once
#include "appframe.h"
class ClearObject:
	public ActorBase3D
{
	using base = ActorBase3D;
public:
	ClearObject( ApplicationBase& game,ModeBase& mode,float _radius );
	virtual ~ClearObject();
	virtual Type GetType()
	{
		return Type::kClearObject;
	}
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage( ModeBase& mode );

protected:
	vector4 _vObjective;  // íÜêSç¿ïW

	int    _handle;
	float radius;
};

