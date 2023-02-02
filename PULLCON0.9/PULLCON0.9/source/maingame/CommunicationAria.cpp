#include "CommunicationAria.h"
CommunicationAria::CommunicationAria( ApplicationBase& game,ModeBase& mode,float collradius, std::string storyname )
	:base( game,mode )
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

bool CommunicationAria::Update(  )
{
	base::Update( );



	return true;
}

bool CommunicationAria::Draw(  )
{
	base::Draw( );
	return true;
}