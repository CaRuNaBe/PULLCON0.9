#include "UIPullGage.h"
namespace
{
	constexpr int  BASE_PULLGAGE_POSI_X = 500;
	constexpr int  BASE_PULLGAGE_POSI_Y = 500;
	int THICKNESS = 0;
}
UIPullGage::UIPullGage( ApplicationBase& game,int layer,ModeBase& _base )
	:UIBase( game,layer,_base )
{
	Initialize();
	THICKNESS = _game.DispSizeH() - 980;
};
UIPullGage:: ~UIPullGage()
{
};

bool UIPullGage::Initialize()
{
	UIBase::Initialize();
	hundle_pullgage[0] = ResourceServer::LoadGraph( "res/player/UI/PullGage/ui_DoPullOut.png" );
	hundle_pullgage[1] = ResourceServer::LoadGraph( "res/player/UI/PullGage/ui_DoPullOutMeter.png" );
	hundle_pullgage[2] = ResourceServer::LoadGraph( "res/player/UI/PullGage/ui_DoPullOutMeter_XButton.png" );
	hundle_pullgage[3] = ResourceServer::LoadGraph( "res/player/UI/PullGage/ui_DoPullOutMeter_XButton_OFF.png" );
	hundle_pullgage[4] = ResourceServer::LoadGraph( "res/player/UI/PullGage/ui_DoPullOutMeterButton_OFF.png" );
	hundle_pullgage[5] = ResourceServer::LoadGraph( "res/player/UI/PullGage/ui_DoPullOutMeterButton_ON.png" );
	hundle_pullgage[6] = ResourceServer::LoadGraph( "res/player/UI/PullGage/ui_DoPullOutMeterButton_Triangle.png" );
	brack = GetColor( 0,0,0 );
	is_hide = true;
	return true;
};

bool UIPullGage::Update()
{
	UIBase::Update();
	is_hide = true;
	for ( auto&& game_object : mode_base.GetObjectServer3D().GetObjects() )
	{
		if ( game_object->GetType() == ActorBase3D::Type::kPlayer )
		{
			auto player = std::static_pointer_cast<Player>(game_object);
			if ( player->GetPlayerState() == Player::State::EVENT )
			{
				is_hide = false;
			}
			break;
		}
	}
	return true;
};

bool UIPullGage::Draw()
{
	UIBase::Draw();
	if ( !is_hide )
	{
		DrawBox( _game.DispBasics(),_game.DispBasics(),_game.DispSizeW(),THICKNESS,brack,TRUE );
		DrawGraph( BASE_PULLGAGE_POSI_X,BASE_PULLGAGE_POSI_Y,hundle_pullgage[1],TRUE );
		//math::Vector2 pos = {};
		for ( int i = 0; i < 7; i++ )
		{
			DrawRotaGraph( BASE_PULLGAGE_POSI_X + 129,BASE_PULLGAGE_POSI_Y + 35,1.0,math::utility::radian_to_degree( 0 ),hundle_pullgage[4],TRUE,TRUE );
		}
		DrawBox( _game.DispBasics(),THICKNESS + 900,_game.DispSizeW(),_game.DispSizeH(),brack,TRUE );
	};
	return true;
};

bool UIPullGage::DebugDraw()
{
	UIBase::DebugDraw();

	return true;
};