#include "UIPullGage.h"
UIPullGage::UIPullGage( ApplicationBase& game,int layer,ModeBase& _base )
	:UIBase( game,layer,_base )
{
	Initialize();
	handle_do_pullout = ResourceServer::LoadGraph( "res/player/UI/PullGage/ui_DoPullOut.png" );
	handle_meter_body = ResourceServer::LoadGraph( "res/player/UI/PullGage/ui_DoPullOutMeter.png" );
	handle_dopulloutmeter_xbutton_on = ResourceServer::LoadGraph( "res/player/UI/PullGage/ui_DoPullOutMeter_XButton.png" );
	handle_dopulloutmeter_xbutton_off = ResourceServer::LoadGraph( "res/player/UI/PullGage/ui_DoPullOutMeter_XButton_OFF.png" );
	hamdle_dopulloutmeterbutton_off = ResourceServer::LoadGraph( "res/player/UI/PullGage/ui_DoPullOutMeterButton_OFF.png" );
	handle_dopulloutmeterbutton_on = ResourceServer::LoadGraph( "res/player/UI/PullGage/ui_DoPullOutMeterButton_ON.png" );
	handle_dopulloutmeterbutton_triangle = ResourceServer::LoadGraph( "res/player/UI/PullGage/ui_DoPullOutMeterButton_Triangle.png" );
};
UIPullGage:: ~UIPullGage()
{
};

bool UIPullGage::Initialize()
{
	UIBase::Initialize();

	return true;
};

bool UIPullGage::Update()
{
	UIBase::Update();
	return true;
};

bool UIPullGage::Draw()
{
	UIBase::Draw();

	return true;
};

bool UIPullGage::DebugDraw()
{
	UIBase::DebugDraw();
	DrawGraph( 500,500,handle_meter_body,TRUE );
	return true;
};