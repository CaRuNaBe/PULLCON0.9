#include "AreaCommunication.h"
#include "../mode/ModeSpeakScript.h"
#include "../mode/ModeMainGame.h"
AreaCommunication::AreaCommunication( ApplicationBase& game,ModeBase& mode,std::string storyname )
	:base( game,mode )
{
	story_name = storyname;

	Init();

}

AreaCommunication::~AreaCommunication()
{

}

void AreaCommunication::Init()
{
	base::Init();

}

bool AreaCommunication::Update()
{
	base::Update();

	for ( auto&& obje : _mode.GetObjectServer3D().GetObjects() )
	{
		if ( (obje->GetType() == ActorBase3D::Type::kPlayer) )
		{
			if ( IsHitObject( *obje ) )
			{
				auto story = std::make_unique<ModeSpeakScript>( _game,30,story_name );
				_game.GetModeServer()->Add( std::move( story ) );
				_mode.GetObjectServer3D().Del( *this );
				break;
			}
		}
	}
	_collision._fRadius = _fRadius * _fScale;
	UpdateCollision();
	return true;
}

bool AreaCommunication::Draw()
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