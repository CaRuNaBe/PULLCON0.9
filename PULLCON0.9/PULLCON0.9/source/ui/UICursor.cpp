#include "UICursor.h"
UICursor::UICursor( ApplicationBase& game,int layer,ModeBase& _base )
	:UIBase( game,layer,_base )
{
	handle_cursor = ResourceServer::LoadGraph( "res/player/UI/cursor/ui_Player_AimCorsor.png" );
	Initialize();
};

UICursor::~UICursor()
{
};

bool UICursor::Initialize()
{
	UIBase::Initialize();
	posi_cursor = {0.0f,0.0f,0.0f};
	return true;
};

bool UICursor::Update()
{
	UIBase::Update();
	for ( auto&& game_object : mode_base.GetObjectServer3D().GetObjects() )
	{
		if ( game_object->GetType() == ActorBase3D::Type::kPlayer )
		{
			posi_cursor = game_object->GetTarget();
			break;
		}
	}
	return true;
};

bool UICursor::Draw()
{
	UIBase::Draw();
	auto ScreenPos = ConvWorldPosToScreenPos( ToDX( posi_cursor ) );
	DrawRotaGraph( static_cast<int>(ScreenPos.x),static_cast<int>(ScreenPos.y),0.5,0,handle_cursor,TRUE );
	return true;
};

bool UICursor::DebugDraw()
{
	UIBase::DebugDraw();
	return true;
};