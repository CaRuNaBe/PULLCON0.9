#include "UIHpGage.h"
namespace
{
	constexpr int BODY_POSI_X = 0;
	constexpr int BODY_POSI_Y = 0;
	constexpr int GAGE_POSI_X = 55;
	constexpr int ALERT_POSI_X = 0;
	constexpr int ALERT_POSI_Y = 881;
	constexpr int GAGE_MAX_WIDTH = 391;
	constexpr int GAGE_MAX_HEIGHT = 63;

	int player_max_hp = 0;
}
UIHpGage::UIHpGage( ApplicationBase& game,int layer,ModeMainGame& _base )
	:UIBase( game,layer,_base )
{
	hp_gage_now_posi = static_cast<float>(GAGE_MAX_WIDTH);
	handle_hp_body = ResourceServer::LoadGraph( "res/2D_image/HPgage/ui_Player_HP_1.png" );
	handle_hp_gage = ResourceServer::LoadGraph( "res/2D_image/HPgage/ui_Player_HP_2.png" );
	handle_hp_alert = ResourceServer::LoadGraph( "res/2D_image/alert/ui_HP_Alert.png" );
	Initialize();
};

UIHpGage::~UIHpGage()
{
};

bool UIHpGage::Initialize()
{
	UIBase::Initialize();
	for ( auto&& game_object : mode_base.GetObjectServer3D().GetObjects() )
	{
		if ( game_object->GetType() == ActorBase3D::Type::kPlayer )
		{
			player_max_hp = game_object->GetLife();
			break;
		}
	}

	is_alert = false;
	return true;
};

bool UIHpGage::Update()
{
	UIBase::Update();
	int player_now_fuel = 0;

	for ( auto&& game_object : mode_base.GetObjectServer3D().GetObjects() )
	{
		if ( game_object->GetType() == ActorBase3D::Type::kPlayer )
		{
			player_now_fuel = game_object->GetLife();
			break;
		}
	}
	float gage_ratio = static_cast<float>(player_now_fuel) / static_cast<float>(player_max_hp);
	hp_gage_now_posi = static_cast<float>(GAGE_MAX_WIDTH) * gage_ratio;
	if(gage_ratio < 0.3f)
	{
		is_alert = true;
	}
	else
	{
		is_alert = false;
	}
	return true;
};

bool UIHpGage::Draw()
{
	UIBase::Draw();
	DrawGraph( BODY_POSI_X,BODY_POSI_Y,handle_hp_body,TRUE );

	DrawRectGraph( GAGE_POSI_X,BODY_POSI_Y,0,0,static_cast<int>(hp_gage_now_posi),GAGE_MAX_HEIGHT,handle_hp_gage,TRUE,FALSE );
	if(is_alert)
	{
		DrawGraph(ALERT_POSI_X, ALERT_POSI_Y, handle_hp_alert, TRUE);
	}
	return true;
};

bool  UIHpGage::DebugDraw()
{
	UIBase::DebugDraw();

	return true;
};