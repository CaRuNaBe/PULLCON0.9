#include "UIFuelGage.h"
namespace
{
	constexpr int BODY_POSI_X = 5;
	constexpr int BODY_POSI_Y = 60;
	constexpr int GAGE_POSI_X = 60;
	constexpr int GAGE_POSI_Y = 60;
	constexpr int ALERT_POSI_X = 0;
	constexpr int ALERT_POSI_Y = 970;
	constexpr int GAGE_MAX_WIDTH = 356;
	constexpr int GAGE_MAX_HEIGHT = 36;

	int player_max_fuel = 0;
}
UIFuelGage::UIFuelGage( ApplicationBase& game,int layer,ModeMainGame& _base )
	:UIBase( game,layer,_base )
{
	fuel_gage_now_posi = static_cast<float>(GAGE_MAX_WIDTH);
	handle_fuel_body = ResourceServer::LoadGraph( "res/2D_image/Fuelgage/ui_Player_Fuel_1.png" );
	handle_fuel_gage = ResourceServer::LoadGraph( "res/2D_image/Fuelgage/ui_Player_Fuel_2.png" );
	handle_fuel_alert = ResourceServer::LoadGraph("res/2D_image/alert/ui_Fuel_Alert.png");
	Initialize();
};

UIFuelGage::~UIFuelGage()
{
};

bool UIFuelGage::Initialize()
{
	UIBase::Initialize();
	for ( auto&& game_object : mode_base.GetObjectServer3D().GetObjects() )
	{
		if ( game_object->GetType() == ActorMainGame::Type::kPlayer )
		{
			player_max_fuel = game_object->GetFuel();
			break;
		}
	}

	is_alert = false;
	return true;
};

bool UIFuelGage::Update()
{
	UIBase::Update();
	int player_now_fuel = 0;

	for ( auto&& game_object : mode_base.GetObjectServer3D().GetObjects() )
	{
		if ( game_object->GetType() == ActorMainGame::Type::kPlayer )
		{
			player_now_fuel = game_object->GetFuel();
			break;
		}
	}
	float gage_ratio = static_cast<float>(player_now_fuel) / static_cast<float>(player_max_fuel);
	fuel_gage_now_posi = static_cast<float>(GAGE_MAX_WIDTH) * gage_ratio;
	if (gage_ratio < 0.3f)
	{
		is_alert = true;
	}
	else
	{
		is_alert = false;
	}
	return true;
};

bool UIFuelGage::Draw()
{
	UIBase::Draw();
	DrawGraph( BODY_POSI_X,BODY_POSI_Y,handle_fuel_body,TRUE );
	DrawRectGraph( GAGE_POSI_X,GAGE_POSI_Y,0,0,static_cast<int>(fuel_gage_now_posi),GAGE_MAX_HEIGHT,handle_fuel_gage,TRUE,FALSE );
	if (is_alert)
	{
		DrawGraph(ALERT_POSI_X, ALERT_POSI_Y, handle_fuel_alert, TRUE);
	}
	return true;
};

bool  UIFuelGage::DebugDraw()
{
	UIBase::DebugDraw();
	return true;
};