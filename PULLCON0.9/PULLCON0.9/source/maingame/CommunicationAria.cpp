#include "CommunicationAria.h"
CommunicationAria::CommunicationAria(int collradius, std::string storyname )
	:base()
{
	story_name = storyname;
	coll_radius = collradius;
	Init();
}

CommunicationAria::~CommunicationAria()
{

}

void CommunicationAria::Init()
{
	base::Init();


}

bool CommunicationAria::Update( ApplicationBase& game,ModeBase& mode )
{
	base::Update( game,mode );



	return true;
}

bool CommunicationAria::Draw( ApplicationBase& game,ModeBase& mode )
{
	base::Draw( game,mode );
	return true;
}