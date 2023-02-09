#include "CommunicationAria.h"
#include "../mode/ModeSpeakScript.h"
#include "../mode/ModeMainGame.h"
CommunicationAria::CommunicationAria( ApplicationBase& game,ModeBase& mode,float collradius,std::string storyname )
	:base( game,mode )
{
	story_name = storyname;

	Init();
	_collision._fRadius = collradius;

}

CommunicationAria::~CommunicationAria()
{

}

void CommunicationAria::Init()
{
	base::Init();
}

bool CommunicationAria::Update()
{
	base::Update();

	for ( auto&& obje : _mode.GetObjectServer3D().GetObjects() )
	{
		if ( (obje->GetType() == ActorBase3D::Type::kPlayer) )
		{
			if ( IsHitObject( *obje ) )
			{
				auto story = std::make_shared<ModeSpeakScript>( _game,30,story_name );
				_game.GetModeServer()->Add( story );
				_mode.GetObjectServer3D().Del( *this );
			}
		}
	}

	return true;
}

bool CommunicationAria::Draw()
{
	base::Draw();
	// ƒRƒŠƒWƒ‡ƒ“•`‰æ
	if ( !((ModeMainGame&)_mode)._dbgCollisionDraw )
	{
		vector4 color = {255, 255, 255};
		DrawCollision( color );
	}
	return true;
}