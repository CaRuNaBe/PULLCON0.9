#include "UICursor.h"
UICursor::UICursor( ApplicationBase& game,int layer,ModeBase& _base )
	:UIBase( game,layer,_base )
{
	handle_cursor = ResourceServer::LoadGraph( "res/player/UI/Fuelgage/ui_Player_Fuel_1.png" );
	Initialize();
};

UICursor::~UICursor()
{
};

bool UICursor::Initialize()
{
	UIBase::Initialize();

	return true;
};

bool UICursor::Update()
{
	UIBase::Update();

	return true;
};

bool UICursor::Draw()
{
	UIBase::Draw();
	return true;
};

bool UICursor::DebugDraw()
{
	UIBase::DebugDraw();
	return true;
};