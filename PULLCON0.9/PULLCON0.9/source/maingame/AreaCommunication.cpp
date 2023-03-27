#include "AreaCommunication.h"
#include "../mode/ModeSpeakScript.h"

#include "../ApplicationGlobal.h"
AreaCommunication::AreaCommunication( ApplicationBase& game,ModeMainGame& mode,std::string storyname )
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

	_collision._fRadius = _fRadius * _fScale;
	for ( auto&& obje : _mode.GetObjectServer3D().GetObjects() )
	{
		if ( (obje->GetType() == ActorBase3D::Type::kPlayer) )
		{
			if ( IsHitObject( *obje ) )
			{
				if ( gGlobal.GetIsEndSpeakScript() )
				{
					gGlobal.IsNotEndSpeakScript();
					PlaySoundMem( gGlobal._se["comm_start"],DX_PLAYTYPE_BACK );
					auto story = std::make_shared<ModeSpeakScript>( _game,30,story_name );
					_game.GetModeServer()->Add( story );

					_mode.GetObjectServer3D().Del( *this );
				}
				break;
			}
		}
	}
	UpdateCollision();
	return true;
}

bool AreaCommunication::Draw()
{
	base::Draw();
	// ƒRƒŠƒWƒ‡ƒ“•`‰æ
#if _DEBUG
	vector4 color = {255, 255, 255};
	DrawCollision( color );
#endif
	return true;
}