#include "UIPullGage.h"
#include "../ApplicationGlobal.h"
namespace
{
	constexpr int  BASE_PULLGAGE_POSI_X = 800;
	constexpr int  BASE_PULLGAGE_POSI_Y = 700;
	math::Vector2 BASE_POS = {BASE_PULLGAGE_POSI_X,BASE_PULLGAGE_POSI_Y};
	int BASE_IMAGE_SIZE_X = 0;
	int BASE_IMAGE_SIZE_Y = 0;
	math::Vector2 BASE_IMAGE_SIZE = {BASE_IMAGE_SIZE_X,BASE_IMAGE_SIZE_Y};
	int THICKNESS = 0;
	math::Vector2 BUTTON_POS = {0,0};
}

UIPullGage::UIPullGage( ApplicationBase& game,int layer,ModeMainGame& _base )
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
	hundle_pullgage[0] = ResourceServer::LoadGraph( "res/2D_image/PullGage/ui_DoPullOut.png" );
	hundle_pullgage[1] = ResourceServer::LoadGraph( "res/2D_image/PullGage/ui_DoPullOutMeter.png" );
	hundle_pullgage[2] = ResourceServer::LoadGraph( "res/2D_image/PullGage/ui_DoPullOutMeterButton_OFF.png" );
	hundle_pullgage[3] = ResourceServer::LoadGraph( "res/2D_image/PullGage/ui_DoPullOutMeterButton_ON.png" );
	hundle_pullgage[4] = ResourceServer::LoadGraph( "res/2D_image/PullGage/ui_DoPullOutMeterButton_Triangle.png" );

	hundle_xbutton[0] = ResourceServer::LoadGraph( "res/2D_image/PullGage/ui_DoPullOutMeter_XButton.png" );
	hundle_xbutton[1] = ResourceServer::LoadGraph( "res/2D_image/PullGage/ui_DoPullOutMeter_XButton_OFF.png" );
	brack = GetColor( 0,0,0 );
	GetGraphSize( hundle_pullgage[1],&BASE_IMAGE_SIZE_X,&BASE_IMAGE_SIZE_Y );
	BASE_IMAGE_SIZE = {BASE_IMAGE_SIZE_X,BASE_IMAGE_SIZE_Y};
	BUTTON_POS = {BASE_POS.IntX() + 92,BASE_POS.IntY() + 130};
	button_on_count = 0;
	player_pull_now_count = 0;
	is_hide = true;
	is_pullok = false;
	return true;
};

bool UIPullGage::Update()
{
	UIBase::Update();
	is_hide = true;
	is_pullok = false;
	button_on_count = 0;
	for ( auto&& game_object : mode_base.GetObjectServer3D().GetObjects() )
	{
		if ( game_object->GetType() == ActorBase3D::Type::kPlayer )
		{
			if ( game_object->GetEvent() == true )
			{
				is_pullok = true;
			}
			auto player = std::static_pointer_cast<Player>(game_object);
			if ( player->GetPlayerState() == Player::State::EVENT )
			{
				is_hide = false;
			}
			button_on_count = (player->GetPush() / 2) + 1;
			player_pull_now_count = player->GetPush();
			break;
		}
	}
	return true;
};

bool UIPullGage::Draw()
{
	UIBase::Draw();
	if ( is_pullok && is_hide )
	{
		DrawGraph( BASE_POS.IntX(),BASE_POS.IntY(),hundle_pullgage[0],TRUE );
	}

	if ( !is_hide )
	{
		DrawBox( _game.DispBasics(),_game.DispBasics(),_game.DispSizeW(),_game.DispBasics() + 100,brack,TRUE );
		DrawGraph( BASE_POS.IntX(),BASE_POS.IntY(),hundle_pullgage[1],TRUE );

		auto BASE_IMAGE_CENTER = BASE_POS.GetCentor( BASE_IMAGE_SIZE );


		math::Polar2 pol = {BASE_IMAGE_CENTER,92.0f,-90.0f};

		for ( int i = 0; i < 9; i++ )
		{
			pol.ThetaIncrement( 45.0f );
			if ( i == 3 )
			{
				continue;
			}
			auto pos = pol.ToVector2();
			auto angle = math::utility::degree_to_radian( pol.GetTheta() + 90 );
			DrawRotaGraph( pos.IntX(),pos.IntY(),1.0,angle,hundle_pullgage[2],TRUE,TRUE );
		}

		pol.SetTheta( -135.0f );
		math::Polar2 triangle_pol = {BASE_IMAGE_CENTER,125.0f,-90.0f};
		float triangle_posi_angle = 0.0f;
		if ( player_pull_now_count < 7 )
		{
			triangle_posi_angle = (static_cast<float>(player_pull_now_count) * 22.5f) + triangle_pol.GetTheta();
		}
		else if ( player_pull_now_count == 7 )
		{
			triangle_posi_angle = triangle_pol.GetTheta() + 180.f;
		}
		else if ( player_pull_now_count > 7 )
		{
			triangle_posi_angle = (triangle_pol.GetTheta() + 180.f) + (static_cast<float>(player_pull_now_count % 6) * 22.5f);
		}
		if ( player_pull_now_count >= 12 )
		{
			triangle_posi_angle = 225.0f;
		}
		triangle_pol.SetTheta( triangle_posi_angle );

		for ( int i = 0; i < 8; i++ )
		{
			pol.ThetaIncrement( 45.0f );
			if ( i == 4 )
			{
				button_on_count += 1;
				continue;
			}
			if ( i == button_on_count )
			{

				break;
			}

			auto pos = pol.ToVector2();
			auto angle = math::utility::degree_to_radian( pol.GetTheta() + 90 );
			DrawRotaGraph( pos.IntX(),pos.IntY(),1.0,angle,hundle_pullgage[3],TRUE,TRUE );
		}


		auto triangle_pos = triangle_pol.ToVector2();
		auto triangle_angle = math::utility::degree_to_radian( triangle_pol.GetTheta() + 90 );
		DrawRotaGraph( triangle_pos.IntX(),triangle_pos.IntY(),1.0,triangle_angle,hundle_pullgage[4],TRUE,TRUE );

		if ( _game.Getinput().GetTrgXinput( XINPUT_BUTTON_X ) )
		{
			DrawGraph( BUTTON_POS.IntX(),BUTTON_POS.IntY(),hundle_xbutton[0],TRUE );
			ChangeVolumeSoundMem(255 * 80 / 100, gGlobal._se["player_pull_button"]);
			PlaySoundMem( gGlobal._se["player_pull_button"],DX_PLAYTYPE_BACK );
		}
		else
		{
			DrawGraph( BUTTON_POS.IntX(),BUTTON_POS.IntY(),hundle_xbutton[1],TRUE );
		}

		DrawBox( _game.DispBasics(),_game.DispSizeH() - 100,_game.DispSizeW(),_game.DispSizeH(),brack,TRUE );
	};

	return true;
};

bool UIPullGage::DebugDraw()
{
	UIBase::DebugDraw();

	return true;
};