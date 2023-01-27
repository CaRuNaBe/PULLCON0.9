#pragma once
#include "appframe.h"
#include "string"
class CommunicationAria:
    public ActorBase3D
{
	using base = ActorBase3D;
public:
	CommunicationAria( int collradius,const std::string storyname );
	virtual ~CommunicationAria();
	virtual Type GetType()
	{
		return Type::kCommunicationAria;
	}
	virtual void Init();
	virtual bool Update( ApplicationBase& game,ModeBase& mode );
	virtual bool Draw( ApplicationBase& game,ModeBase& mode );

protected:
	 std::string story_name;
	int coll_radius;
};


