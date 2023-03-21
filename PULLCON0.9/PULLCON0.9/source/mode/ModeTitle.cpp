#include "ModeTitle.h"
#include "../ApplicationMain.h"
#include "../ApplicationGlobal.h"
#include "ModeMainGame.h"
#include "ModeSpeakScript.h"
#include "../title/TitlePlayer.h"
#include "../title/TitleLogo.h"

#include "../title/CreditLogo.h"
#include "../title/CreditGuid.h"
#include "../title/StartLogo.h"
#include "../title/StartGuid.h"
#include "../title/EndLogo.h"
#include "../title/EndGuid.h"
namespace
{	//jsonファイル関係
	const std::string FILENAME = "pullcon0.9.json";//ファイル名
	const std::string FILEPASS = "res/string_date/gamescript/" + FILENAME;//ファイルパス
	const std::string GAMESCRIPT = "pullcon0.9";//スクリプト名
	constexpr int START_UP_LINE = 600;
}


ModeTitle::ModeTitle( ApplicationBase& game,int layer )
	:GameBase( game,layer )
{
	title_state = State::BASE;
	auto titlelogo = std::make_shared<TitleLogo>( game,0,*this );
	object_out_game.Add( titlelogo );

	auto creditlogo = std::make_shared<CreditLogo>( game,1,*this );
	object_out_game.Add( creditlogo );
	auto startlogo = std::make_shared<StartLogo>( game,2,*this );
	object_out_game.Add( startlogo );
	auto endlogo = std::make_shared<EndLogo>( game,3,*this );
	object_out_game.Add( endlogo );

	auto creditguid = std::make_shared<CreditGuid>( game,4,*this );
	object_out_game.Add( creditguid );
	auto startguid = std::make_shared<StartGuid>( game,5,*this );
	object_out_game.Add( startguid );
	auto endguid = std::make_shared<EndGuid>( game,6,*this );
	object_out_game.Add( endguid );

	auto player = std::make_shared<TitlePlayer>( game,7,*this );
	object_out_game.Add( player );
	PlaySoundFile( "res/sound/title/title_bgm.wav",DX_PLAYTYPE_LOOP );
	Initialize();
};

ModeTitle::~ModeTitle()
{
	StopSoundFile();
};

bool ModeTitle::Initialize()
{
	return true;
}

bool ModeTitle::Update()
{
	object_out_game.Update();
	switch ( title_state )
	{
		case ModeTitle::State::BASE:
			for ( auto&& obje : object_out_game.GetObjects() )
			{
				if ( (obje->GetType() == ActorTitle::Type::KGAMESTARTLOGO) )
				{
					if ( obje->GetPosition().y < START_UP_LINE )
					{
						_game.GetInstance()->GetModeServer()->Del( *this );
						auto game = std::make_shared<ModeMainGame>( _game,1 );
						game->Initialize( FILEPASS,GAMESCRIPT,FILENAME );
						_game.GetInstance()->GetModeServer()->Add( game );
						break;
					}
#if _DEBUG
					if ( _game.Getinput().GetKeyXinput( XINPUT_BUTTON_A ) )
					{
						_game.GetInstance()->GetModeServer()->Del( *this );
						auto game = std::make_shared<ModeMainGame>( _game,1 );
						game->Initialize( FILEPASS,GAMESCRIPT,FILENAME );
						_game.GetInstance()->GetModeServer()->Add( game );
						break;
					}
#endif // _DEBUG
				}
				if ( (obje->GetType() == ActorTitle::Type::KCREDITLOGO) )
				{
					if ( obje->GetPosition().y < START_UP_LINE )
					{
						auto credit = std::make_shared<ModeSpeakScript>( _game,99,"credit/credit" );
						_game.GetInstance()->GetModeServer()->Add( credit );
						gGlobal.IsNotEndSpeakScript();
						title_state = State::CREDIT;
						break;
					}
				}
				if ( (obje->GetType() == ActorTitle::Type::KENDLOGO) )
				{
					if ( obje->GetPosition().y < START_UP_LINE )
					{
						_game.IsGameEnd();
						_game.GetInstance()->GetModeServer()->Del( *this );
						break;
					}
				}
			}
			break;
		case ModeTitle::State::CREDIT:
			if ( gGlobal.GetIsEndSpeakScript() )
			{
				for ( auto&& obje : object_out_game.GetObjects() )
				{
					obje->Initialize();
				}
				title_state = State::BASE;
			}
			break;
		default:
			break;
	}

	return true;
}

bool ModeTitle::Draw()
{
	object_out_game.Draw();
	return true;
}

bool ModeTitle::DebugDraw()
{
	return true;
};