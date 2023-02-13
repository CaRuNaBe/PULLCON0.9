#include "UIHpGage.h"
namespace
{
	constexpr int BODY_POSI_X = 0;
	constexpr int BODY_POSI_Y = 0;
	constexpr int GAGE_POSI_X = 55;
	constexpr int GAGE_MAX_WIDTH = 391;
	constexpr int GAGE_MAX_HEIGHT = 63;

	int player_max_hp = 0;
}
UIHpGage::UIHpGage( ApplicationBase& game,int layer,ModeBase& _base )
	:BaseUI( game,layer,_base )
{
	handle_hp_body = ResourceServer::LoadGraph( "res/player/UI/HPgage/ui_Player_HP_1.png" );
	handle_hp_gage = ResourceServer::LoadGraph( "res/player/UI/HPgage/ui_Player_HP_2.png" );
	for ( auto&& game_object : mode_base.GetObjectServer3D().GetObjects() )
	{
		if ( game_object->GetType() == ActorBase3D::Type::kPlayer )
		{
			player_max_hp = game_object->GetLife();
		}
	}
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
	BaseUI::Update();
	int player_now_fuel = 0;

	for ( auto&& game_object : mode_base.GetObjectServer3D().GetObjects() )
	{
		if ( game_object->GetType() == ActorBase3D::Type::kPlayer )
		{
			player_now_fuel = game_object->GetLife();
		}
	}
	float gage_ratio = static_cast<float>(player_now_fuel) / static_cast<float>(player_max_hp);
	hp_gage_now_posi = static_cast<float>(GAGE_MAX_WIDTH) * gage_ratio;
	return true;
};

bool UIHpGage::Draw()
{
	BaseUI::Draw();
	DrawGraph( BODY_POSI_X,BODY_POSI_Y,handle_hp_body,TRUE );

	DrawRectGraph( GAGE_POSI_X,BODY_POSI_Y,0,0,hp_gage_now_posi,GAGE_MAX_HEIGHT,handle_hp_gage,TRUE,FALSE );
	return true;
};

bool  UIHpGage::DebugDraw()
{
	BaseUI::DebugDraw();

	return true;
};