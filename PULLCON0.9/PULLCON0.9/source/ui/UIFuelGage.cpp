#include "UIFuelGage.h"

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
	DrawGraph( 5,60,handle_fuel_body,TRUE );
	DrawGraph( 60,60,handle_fuel_gage,TRUE );
	return true;
};

bool  UIFuelGage::DebugDraw()
{
	BaseUI::DebugDraw();
	return true;
};