#pragma once
#include "appframe.h"
#include "string"
class CommunicationAria:
	public ActorBase3D
{
	using base = ActorBase3D;
public:
	CommunicationAria( ApplicationBase& game,ModeBase& mode,float collradius,const std::string storyname );
	virtual ~CommunicationAria();
	virtual Type GetType()
	{
		return Type::kCommunicationAria;
	}
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

protected:
	std::string story_name;
	float coll_radius;
};


