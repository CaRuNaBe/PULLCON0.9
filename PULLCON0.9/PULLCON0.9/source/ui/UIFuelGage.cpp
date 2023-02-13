#include "UIFuelGage.h"
namespace
{
	constexpr int BODY_POSI_X = 5;
	constexpr int BODY_POSI_Y = 60;
	constexpr int GAGE_POSI_X = 60;
	constexpr int GAGE_POSI_Y = 60;
	constexpr int GAGE_MAX_WIDTH = 356;
	constexpr int GAGE_MAX_HEIGHT = 36;

	int player_max_fuel = 0;
}
UIFuelGage::UIFuelGage( ApplicationBase& game,int layer,ModeBase& _base )
	:BaseUI( game,layer,_base )
{
	fuel_gage_now_posi = static_cast<float>(GAGE_MAX_WIDTH);
	handle_fuel_body = ResourceServer::LoadGraph( "res/player/UI/Fuelgage/ui_Player_Fuel_1.png" );
	handle_fuel_gage = ResourceServer::LoadGraph( "res/player/UI/Fuelgage/ui_Player_Fuel_2.png" );
	for ( auto&& game_object : mode_base.GetObjectServer3D().GetObjects() )
	{
		if ( game_object->GetType() == ActorBase3D::Type::kPlayer )
		{
			player_max_fuel = game_object->GetFuel();
		}
	}
};

UIFuelGage::~UIFuelGage()
{
};

bool UIFuelGage::Initialize()
{
	BaseUI::Initialize();
	return true;
};

bool UIFuelGage::Update()
{
	BaseUI::Update();
	int player_now_fuel = 0;

	for ( auto&& game_object : mode_base.GetObjectServer3D().GetObjects() )
	{
		if ( game_object->GetType() == ActorBase3D::Type::kPlayer )
		{
			player_now_fuel = game_object->GetFuel();
		}
	}
	float gage_ratio = static_cast<float>(player_now_fuel) / static_cast<float>(player_max_fuel);
	fuel_gage_now_posi = static_cast<float>(GAGE_MAX_WIDTH) * gage_ratio;
	return true;
};

bool UIFuelGage::Draw()
{
	BaseUI::Draw();
	DrawGraph( BODY_POSI_X,BODY_POSI_Y,handle_fuel_body,TRUE );
	DrawRectGraph( GAGE_POSI_X,GAGE_POSI_Y,0,0,static_cast<int>(fuel_gage_now_posi),GAGE_MAX_HEIGHT,handle_fuel_gage,TRUE,FALSE );
	return true;
};

bool  UIFuelGage::DebugDraw()
{
	BaseUI::DebugDraw();
	return true;
};