#pragma once
#include "appframe.h"
#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
class AreaNoEntry:
	public ActorBase3D
{
	using base = ActorBase3D;
public:
	AreaNoEntry( ApplicationBase& game,ModeMainGame& mode );
	virtual ~AreaNoEntry();
	virtual Type GetType() { return Type::kStageObject; }
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

protected:

};

