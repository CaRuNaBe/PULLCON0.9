#include "ModeTitle.h"
#include "../ApplicationMain.h"
#include "ModeMainGame.h"
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
}
ModeTitle::ModeTitle( ApplicationBase& game,int layer )
	:GameBase( game,layer )
{
	auto titlelogo = std::make_shared<TitleLogo>( game,*this );
	object_out_game.Add( titlelogo );

	auto creditlogo = std::make_shared<CreditLogo>( game,*this );
	object_out_game.Add( creditlogo );
	auto startlogo = std::make_shared<StartLogo>( game,*this );
	object_out_game.Add( startlogo );
	auto endlogo = std::make_shared<EndLogo>( game,*this );
	object_out_game.Add( endlogo );

	auto creditguid = std::make_shared<CreditGuid>( game,*this );
	object_out_game.Add( creditguid );
	auto startguid = std::make_shared<StartGuid>( game,*this );
	object_out_game.Add( startguid );
	auto endguid = std::make_shared<EndGuid>( game,*this );
	object_out_game.Add( endguid );

	auto player = std::make_shared<TitlePlayer>( game,*this );
	object_out_game.Add( player );
	Initialize();
};

ModeTitle::~ModeTitle()
{};

bool ModeTitle::Initialize()
{
	return true;
}

bool ModeTitle::Update()
{
	object_out_game.Update();
	for ( auto&& obje : object_out_game.GetObjects() )
	{
		if ( (obje->GetType() == ActorBase2d::Type::KGAMESTARTLOGO) )
		{
			if ( obje->GetPosition().y < 100 )
			{
				_game.GetInstance()->GetModeServer()->Del( *this );
				auto game = std::make_shared<ModeMainGame>( _game,1 );
				game->Initialize( FILEPASS,GAMESCRIPT,FILENAME );
				_game.GetInstance()->GetModeServer()->Add( game );
			}
#if _DEBUG
			if (_game.Getinput().GetKeyXinput(XINPUT_BUTTON_A)) {
				_game.GetInstance()->GetModeServer()->Del(*this);
				auto game = std::make_shared<ModeMainGame>(_game, 1);
				game->Initialize(FILEPASS, GAMESCRIPT, FILENAME);
				_game.GetInstance()->GetModeServer()->Add(game);
		}
#endif // _DEBUG

		}
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