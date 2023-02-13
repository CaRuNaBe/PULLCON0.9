#include "UIFuelGage.h"
namespace
{
	constexpr int BODY_POSI_X = 5;
	constexpr int BODY_POSI_Y = 60;
	constexpr int GAGE_POSI_X = 60;
	constexpr int GAGE_POSI_Y = 60;
	constexpr int GAGE_MAX_WIDTH = 356;
	constexpr int GAGE_MAX_HEIGHT = 36;
}
UIFuelGage::UIFuelGage( ApplicationBase& game,int layer,ModeBase& _base )
	:BaseUI( game,layer,_base )
{
	handle_fuel_body = ResourceServer::LoadGraph( "res/player/UI/Fuelgage/ui_Player_Fuel_1.png" );
	handle_fuel_gage = ResourceServer::LoadGraph( "res/player/UI/Fuelgage/ui_Player_Fuel_2.png" );
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
	return true;
};

bool UIFuelGage::Draw()
{
	BaseUI::Draw();
	DrawGraph( BODY_POSI_X,BODY_POSI_Y,handle_fuel_body,TRUE );
	DrawRectGraph( GAGE_POSI_X,GAGE_POSI_Y,0,0,GAGE_MAX_WIDTH - 100,GAGE_MAX_HEIGHT,handle_fuel_gage,TRUE,FALSE );
	return true;
};

bool  UIFuelGage::DebugDraw()
{
	BaseUI::DebugDraw();
	return true;
};