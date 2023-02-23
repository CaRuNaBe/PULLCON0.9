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
	is_hide = false;
	return true;
};

bool UICursor::Update()
{
	UIBase::Update();
	is_hide = false;
	for ( auto&& game_object : mode_base.GetObjectServer3D().GetObjects() )
	{
		if ( game_object->GetType() == ActorBase3D::Type::kPlayer )
		{
			posi_cursor = game_object->GetTarget();
			auto player = std::static_pointer_cast<Player>(game_object);
			if ( player->GetPlayerState() == Player::State::EVENT || player->GetPlayerState() == Player::State::EVENT )
			{
				is_hide = true;
			}
			break;
		}
	}
	return true;
};

bool UICursor::Draw()
{
	UIBase::Draw();
	if ( !is_hide )
	{
		auto ScreenPos = ConvWorldPosToScreenPos( ToDX( posi_cursor ) );
		DrawRotaGraph( static_cast<int>(ScreenPos.x),static_cast<int>(ScreenPos.y),0.2f,0,handle_cursor,TRUE );
	}
	return true;
};

bool UICursor::DebugDraw()
{
	UIBase::DebugDraw();
	return true;
};