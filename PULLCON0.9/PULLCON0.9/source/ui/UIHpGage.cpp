#include "UIHpGage.h"
UIHpGage::UIHpGage( ApplicationBase& game,int layer,ModeBase& _base )
	:BaseUI( game,layer,_base )
{
	handle_hp_body = ResourceServer::LoadGraph( "res/player/UI/HPgage/ui_Player_HP_1.png" );
	handle_hp_gage = ResourceServer::LoadGraph( "res/player/UI/HPgage/ui_Player_HP_2.png" );
};

UIHpGage::~UIHpGage()
{
};

bool UIHpGage::Initialize()
{
	BaseUI::Initialize();
	return true;
};

bool UIHpGage::Update()
{
	BaseUI::Initialize();
	return true;
};

bool UIHpGage::Draw()
{
	BaseUI::Initialize();
	DrawGraph( 0,0,handle_hp_body,TRUE );
	DrawGraph( 55,0,handle_hp_gage,TRUE );
	return true;
};

bool  UIHpGage::DebugDraw()
{
	BaseUI::DebugDraw();
	return true;
};