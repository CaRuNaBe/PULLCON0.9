#pragma once
#include "appframe.h"
#include "string"
class AreaCommunication:
	public ActorBase3D
{
	using base = ActorBase3D;
public:
	AreaCommunication( ApplicationBase& game,ModeBase& mode,const std::string storyname );
	virtual ~AreaCommunication();
	virtual Type GetType()
	{
		return Type::kAreaCommunication;
	}
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

protected:
	std::string story_name;
};


