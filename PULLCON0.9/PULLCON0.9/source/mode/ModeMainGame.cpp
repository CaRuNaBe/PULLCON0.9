/*****************************************************************//**
 * \file   ModeGame.cpp
 * \brief  ゲームモード実装
 *
 * \author 阿部健太郎
 * \date   September 2022
 *********************************************************************/

#include "ModeMainGame.h"
#include <DxLib.h>
#include "../ApplicationMain.h"
#include"../maingame/Player.h"
#include"../maingame/GameStage.h"
#include"../maingame/SkySphere.h"
#include "../maingame/SupplyEria.h"
#include"../maingame/ClearObject.h"
#include "../maingame/EnemyAAA.h"

namespace
{
	// スクリプト コマンド
	const std::string COMMAND_STAGELABEL = "StageLabel";
	const std::string COMMAND_JUNPLABEL = "StageJunp";
	const std::string COMMAND_CHOICE = "StageChoice";
	const std::string COMMAND_GAMESTART = "Start";//ゲームスタート
	const std::string COMMAND_END = "End";//ゲーム終了
	const std::string COMMAND_LOADING = "Load";//ロード画面表示
	const std::string COMMAND_FEEDIN = "FeedIn";
	const std::string COMMAND_FEEDOUT = "FeedOut";
	const std::string COMMAND_TIMEWAIT = "TimeWait";
	const std::string COMMAND_CLICK = "ClickWait";

	const std::string COMMAND_ADDSTAGE = "Stage";//1
	const std::string COMMAND_ADDSKYSPHERE = "SkySphere";//1
	const std::string COMMAND_ADDNORMALOBJECT = "Object";
	const std::string COMMAND_ADDCLEAROBJECT = "ClearObject";//1
	const std::string COMMAND_ADDAREAENEMYAAA = "AreaEnemyaaa";//1
	const std::string COMMAND_ADDAREAENEMYSPAWN = "AreaEnemySpawn";
	const std::string COMMAND_ADDAREASUPPLY = "AreaSupply";
	const std::string COMMAND_ADDAREACOMMUNICATION = "AreaCommunication";
	const std::string COMMAND_ADDAREANOENTRY = "AreaNoEntry";
	const std::string COMMAND_ADDENEMYAAA = "EnemyAAA";//1
	const std::string COMMAND_ADDPLAYER = "Player";//1

	//編集コマンド
	const std::string ECOMMAND_ADD = "add";
	const std::string ECOMMAND_DELETE = "delete";
	const std::string ECOMMAND_CLEAR = "clear";
	const std::string ECOMMAND_JUNP = "junp";
	const std::string ECOMMAND_SAVE = "save";
}

ModeMainGame::ModeMainGame( ApplicationMain& game,int layer )
	: ModeBase( game,layer )
{
	scripts_data = std::make_shared<ScriptsData>();
	state = ScriptState::PREPARSING;
#if _DEBUG
	state = ScriptState::EDIT;
#endif
	max_line = 0;
	now_line = 0;
	feedcount = 0.0;
	_Alpha = 0;
	is_notcant = false;
	is_notcommand = false;
	is_cannotdelete = false;
	const std::string FILENAME = "pullcon0.9.json";
	const std::string FILEPASS = "res/script/gamescript/" + FILENAME;
	const std::string GAMESCRIPT = "pullcon0.9";
	Initialize( FILEPASS,GAMESCRIPT,FILENAME );
	/*
	state = ScriptState::GAME;
	auto stage = std::make_shared<GameStage>();
	_3D_objectServer.Add( stage );
	auto skysphere = std::make_shared<SkySphere>();
	_3D_objectServer.Add( skysphere );
	auto supplyeria = std::make_shared<SupplyEria>();
	_3D_objectServer.Add( supplyeria );
	auto clearobject = std::make_shared<ClearObject>();
	_3D_objectServer.Add( clearobject );
	auto enemyAAA = std::make_shared<EnemyAAA>();
	_3D_objectServer.Add( enemyAAA );
	auto player = std::make_shared<Player>();
	_3D_objectServer.Add( player );
	*/
}

ModeMainGame::~ModeMainGame()
{
	Destroy();
}

void ModeMainGame::Destroy()
{

	state = ScriptState::PARSING;
	max_line = 0;
	now_line = 0;
	wait_count = 0;
	const std::string FILENAME = "pullcon0.9.json";
	const std::string GAMESCLIPT = "pullcon0.9";
	scripts_data->WriteJson( FILENAME,GAMESCLIPT );
}
/**
 *¥fn void ModeGame::Init_modegame.
 *¥brief
 *¥return void
 */
void ModeMainGame::Initialize( std::string jsonpath,std::string scriptsname,std::string jsonname )
{
	ModeBase::Initialize();

	if ( !scripts_data->LoadJson( jsonpath,scriptsname,jsonname ) )
	{
		return;
	}

	max_line = scripts_data->GetScriptNum();

	if ( max_line <= 0 )
	{
		state = ScriptState::EDIT;
		return;
	}

	//PreParsing();


	return;
};
/**
 *¥fn void ModeGame::Update.
 *¥brief 計算処理毎回呼ばれる
 *¥return void
 */
bool ModeMainGame::Update()
{
	ModeBase::Update();
	_3D_objectServer.Update( _game,*this );

	switch ( state )
	{
		case ScriptState::EDIT:

			break;

		case ScriptState::PREPARSING:
			PreParsing();
			break;

		case ScriptState::PARSING:
			Parsing();
			break;

		case ScriptState::GAME:
			break;

		case ScriptState::STORY:
			break;

		case ScriptState::RESULT:
			break;

		case ScriptState::CRFEEDIN:
			CrfiUpdate();
			break;

		case ScriptState::CRFEEDOUT:
			CrfoUpdate();
			break;

		case ScriptState::TIME_WAIT:
			TimeWait();
			break;

		case ScriptState::CLICK_WAIT:
			ClickWait();
			break;

		case ScriptState::LOADING:
			break;

		case ScriptState::END:
			break;
	}


	return true;
}
/**
 * @fn void ModeMainGame::CrfiUpdate ()
 * @brief スクリプトの "fi" コマンド時の計算処理
 */
void ModeMainGame::CrfiUpdate()
{
	auto i = 255 / feedcount;


	if ( _Alpha > 0.0 )
	{
		_Alpha -= i;
	}
	else
	{
		_Alpha = 0.0;
		state = ScriptState::PARSING;
	}
}
/**
 * @fn void ModeMainGame::CrfoUpdate ()
 * @brief スクリプトの "fo" コマンド時の計算処理
 */
void ModeMainGame::CrfoUpdate()
{
	auto i = 255.0 / feedcount;


	if ( _Alpha < 255.0 )
	{
		_Alpha += i;
	}
	else
	{
		_Alpha = 255.0;
		state = ScriptState::PARSING;
	}
}
//!
//! @fn void ModeMainGame::ClickWait()
//! @brief クリック待ち処理
//!
void ModeMainGame::ClickWait()
{
}
//!
//! @fn void ModeMainGame::TimeWait()
//! @brief 時間待ち処理
//!
void ModeMainGame::TimeWait()
{
	if ( wait_count > 0 )
	{
		--wait_count;
	}
	else
	{
		state = ScriptState::PARSING;
	}
}

bool ModeMainGame::OnCommandAddPLayer( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	const size_t SCRIPTSIZE = 4;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[1],posi.x )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[2],posi.y )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[3],posi.z )) )
	{
		return false;
	}

	auto player = std::make_shared<Player>();
	player->SetPosition( posi );
	_3D_objectServer.Add( player );
	return true;
};

bool ModeMainGame::OnCommandAddStage( unsigned int line,const std::vector<std::string>& scripts )
{
	const size_t SCRIPTSIZE = 2;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	auto stage = std::make_shared<GameStage>();
	_3D_objectServer.Add( stage );
	return true;
};

bool ModeMainGame::OnCommandAddSkySphere( unsigned int line,const std::vector<std::string>& scripts )
{
	const size_t SCRIPTSIZE = 2;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	auto skysphere = std::make_shared<SkySphere>();
	_3D_objectServer.Add( skysphere );
	return true;
};

bool ModeMainGame::OnCommandAddClearObject( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	const size_t SCRIPTSIZE = 4;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[1],posi.x )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[2],posi.y )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[3],posi.z )) )
	{
		return false;
	}
	auto clearobject = std::make_shared<ClearObject>();
	clearobject->SetPosition( posi );
	_3D_objectServer.Add( clearobject );
	return true;
};

bool ModeMainGame::OnCommandAddAreaSupply( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	const size_t SCRIPTSIZE = 4;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[1],posi.x )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[2],posi.y )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[3],posi.z )) )
	{
		return false;
	}
	auto supplyeria = std::make_shared<SupplyEria>();
	supplyeria->SetPosition( posi );
	_3D_objectServer.Add( supplyeria );
	return true;
};

bool ModeMainGame::OnCommandAddEnemyAAA( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	const size_t SCRIPTSIZE = 4;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[1],posi.x )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[2],posi.y )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[3],posi.z )) )
	{
		return false;
	}
	auto enemyAAA = std::make_shared<EnemyAAA>();
	enemyAAA->SetPosition( posi );
	_3D_objectServer.Add( enemyAAA );
	return true;
};

bool ModeMainGame::OnCommandAddAreaEnemyAAA( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	const size_t SCRIPTSIZE = 6;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[1],posi.x )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[2],posi.y )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[3],posi.z )) )
	{
		return false;
	}
	float range = 0.0f;
	if ( !(string::ToFloat( scripts[4],range )) )
	{
		return false;
	}

	int max = 1;
	if ( !(string::ToInt( scripts[5],max )) )
	{
		return false;
	}

	for ( int i = 0; i < max; i++ )
	{
		vector4 AAAposi = {static_cast<float>(utility::get_random( posi.x,posi.x + range ))
			,posi.z
			,static_cast<float>(utility::get_random( posi.y,posi.y + range ))};

		auto enemyAAA = std::make_shared<EnemyAAA>();
		enemyAAA->SetPosition( AAAposi );
		_3D_objectServer.Add( enemyAAA );
	}
	return true;
};

bool ModeMainGame::OnCommandStart( unsigned int line,const std::vector<std::string>& scripts )
{
	const size_t SCRIPTSIZE = 2;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	state = ScriptState::GAME;
	return true;
};
/**
 * @fn bool ScriptEngine::OnCommandCrfi(unsigned int line, const std::vector<std::string>& scripts)
 * @brief スクリプトの 'fi' コマンドを処理
 * \param [in] scripts スクリプトの内容
 * \param [in] scripts スクリプトの内容
 * \return 処理の成否
 */
bool ModeMainGame::OnCommandCrfi( unsigned int line,const std::vector<std::string>& scripts )
{
	crfo_list.clear();
	auto crfi = std::make_unique<CommandCrfi>( line,scripts );
	if ( !crfi->Check() )
	{
		return false;
	}
	feedcount = static_cast<double>(crfi->GetinCount());
	crfi_list.emplace_back( std::move( crfi ) );
	_Alpha = 255.0;
	state = ScriptState::CRFEEDIN;

	return  true;
}
/**
 * @fn bool ScriptEngine::OnCommandCrfo(unsigned int line, const std::vector<std::string>& scripts)
 * @brief スクリプトの "fo" コマンドを処理
 * \param [in] scripts スクリプトの内容
 * \param [in] scripts スクリプトの内容
 * \return 処理の成否
 */
bool ModeMainGame::OnCommandCrfo( unsigned int line,const std::vector<std::string>& scripts )
{
	crfi_list.clear();
	auto crfo = std::make_unique<CommandCrfo>( line,scripts );
	if ( !crfo->Check() )
	{
		return false;
	}
	feedcount = static_cast<double>(crfo->GetoutCount());
	crfo_list.emplace_back( std::move( crfo ) );
	_Alpha = 0.0;
	state = ScriptState::CRFEEDOUT;
	return true;
}

void ModeMainGame::Edit()
{
	int None = 0;
	if ( (state == ScriptState::EDIT) && (CheckHitKey( KEY_INPUT_RETURN ) == 1) )
	{
		FunctionEditCommand editCommand;//文字列でのスイッチ文
		editCommand.insert( std::make_pair( ECOMMAND_ADD,&ModeMainGame::OnEditCommandAdd ) );
		editCommand.insert( std::make_pair( ECOMMAND_DELETE,&ModeMainGame::OnEditCommandDelete ) );
		editCommand.insert( std::make_pair( ECOMMAND_CLEAR,&ModeMainGame::OnEditCommandClear ) );
		editCommand.insert( std::make_pair( ECOMMAND_JUNP,&ModeMainGame::OnEditCommandSave ) );
		editCommand.insert( std::make_pair( ECOMMAND_SAVE,&ModeMainGame::OnEditCommandJunp ) );

		int x = 0; int y = 0;
		std::string buf = "";
		auto cchar = const_cast<char*>(buf.c_str());
		DrawString( x,y,"コマンドを入力してください\nESCで戻る\nadd:オブジェクトの追加\ndelete:オブジェクトの消去\nclear:いま追加されているゲームコマンドを初期化コマンド\nsave:ファイルに書き込み",GetColor( 255,255,255 ) );
		if ( is_notcant )
		{
			is_notcant = false;
			DrawString( x,150,"追加できませんでした\n",GetColor( 255,255,255 ) );
		}
		if ( is_notcommand )
		{
			is_notcommand = false;
			DrawString( x,200,"そのようなコマンドはありません\n",GetColor( 255,255,255 ) );
		}
		if ( is_cannotdelete )
		{
			is_cannotdelete = true;
			DrawString( x,250,"消去出来ませんでした\n",GetColor( 255,255,255 ) );
		}
		if ( KeyInputSingleCharString( 0,500,30,cchar,TRUE ) == 1 )
		{
			std::string ecommandbuf = cchar;
			ClearDrawScreen();
			if ( editCommand.count( ecommandbuf ) <= None )
			{
				is_notcommand = true;
				return;
			}

			(this->*editCommand[ecommandbuf])();

		}
		else
		{
			now_line = 0;
			max_line = scripts_data->GetScriptNum();
			state = ScriptState::PARSING;
		};
	}
}

bool ModeMainGame::OnEditCommandAdd()
{
	int x,y;
	x = y = 0;
	std::string buf;
	auto cchar = const_cast<char*>(buf.c_str());
	DrawString( x,y,"何を追加しますか\n追加できるもの\nStage\nSkySphere\nPlayer,x座標の位置,y座標の位置,z座標の位置\nClearObject,x座標の位置,y座標の位置,z座標の位置\nAreaEnemyaaa,x座標の位置,y座標の位置,z座標の位置,円の範囲,何個出すか\nEnemyAAA,x座標の位置,y座標の位置,z座標の位置\nStart\nEnd",GetColor( 255,255,255 ) );
	if ( KeyInputSingleCharString( 0,500,30,cchar,TRUE ) == 1 )
	{
		std::string ecommandbuf = cchar;

		if ( CheckInputString( ecommandbuf ) )
		{
			scripts_data->ScriptAdd( ecommandbuf );
		}
		else
		{
			ClearDrawScreen();
			is_notcant = true;
		}
	}
	return true;
};
bool ModeMainGame::OnEditCommandDelete()
{
	int x,y;
	x = y = 0;
	std::string buf = "";
	auto cchar = const_cast<char*>(buf.c_str());
	DrawString( x,y,"何を消去しますか\n番号を入力してください",GetColor( 255,255,255 ) );
	y += 30;
	auto maxline = scripts_data->GetScriptNum();
	for ( unsigned int i = 0; i <= maxline; i++ )
	{
		DrawString( x,y,scripts_data->GetScriptLine( i ).c_str(),GetColor( 255,255,255 ) );
		y += 30;
	}
	if ( KeyInputSingleCharString( 0,500,30,cchar,TRUE ) == 1 )
	{
		int deliteLine = 0;
		std::string ecommandbuf = cchar;
		string::ToInt( ecommandbuf,deliteLine );
		deliteLine--;
		if ( deliteLine < 0 )
		{
			is_cannotdelete = true;
			return false;
		}
		scripts_data->ScriptDelete( deliteLine );
	}
	return true;
};
bool ModeMainGame::OnEditCommandClear()
{
	scripts_data->ScriptClear();
	return true;
};
bool ModeMainGame::OnEditCommandSave()
{
	const std::string FILENAME = "pullcon0.9.json";
	const std::string GAMESCLIPT = "pullcon0.9";
	scripts_data->WriteJson( FILENAME,GAMESCLIPT );
	return true;
};
bool ModeMainGame::OnEditCommandJunp()
{
	return true;
};

bool ModeMainGame::CheckInputString( std::string command )
{
	auto script = string::Split( command,"," );

	FunctionGameCommand comand_funcs;
	comand_funcs.insert( std::make_pair( COMMAND_ADDPLAYER,&ModeMainGame::OnCommandAddPLayer ) );
	comand_funcs.insert( std::make_pair( COMMAND_ADDSTAGE,&ModeMainGame::OnCommandAddStage ) );
	comand_funcs.insert( std::make_pair( COMMAND_ADDSKYSPHERE,&ModeMainGame::OnCommandAddSkySphere ) );
	comand_funcs.insert( std::make_pair( COMMAND_ADDCLEAROBJECT,&ModeMainGame::OnCommandAddClearObject ) );
	comand_funcs.insert( std::make_pair( COMMAND_ADDAREASUPPLY,&ModeMainGame::OnCommandAddAreaSupply ) );
	comand_funcs.insert( std::make_pair( COMMAND_ADDENEMYAAA,&ModeMainGame::OnCommandAddEnemyAAA ) );
	comand_funcs.insert( std::make_pair( COMMAND_ADDAREAENEMYAAA,&ModeMainGame::OnCommandAddAreaEnemyAAA ) );
	comand_funcs.insert( std::make_pair( COMMAND_GAMESTART,&ModeMainGame::OnCommandStart ) );
	comand_funcs.insert( std::make_pair( COMMAND_FEEDIN,&ModeMainGame::OnCommandCrfi ) );
	comand_funcs.insert( std::make_pair( COMMAND_FEEDOUT,&ModeMainGame::OnCommandCrfo ) );
	if ( command.size() <= 0 )
	{
		return false;
	}

	if ( comand_funcs.count( script[0] ) <= 0 )
	{
		return false;
	}

	if ( !(this->*comand_funcs[script[0]])(now_line,script) )
	{
		return false;
	};
	state = ScriptState::EDIT;
	_3D_objectServer.Clear();
	return true;
}

void ModeMainGame::PreParsing()
{
}

void ModeMainGame::Parsing()
{
	auto stop_parsing = false;
	unsigned	int dateempty = 0;
	FunctionGameCommand comand_funcs;
	comand_funcs.insert( std::make_pair( COMMAND_ADDPLAYER,&ModeMainGame::OnCommandAddPLayer ) );
	comand_funcs.insert( std::make_pair( COMMAND_ADDSTAGE,&ModeMainGame::OnCommandAddStage ) );
	comand_funcs.insert( std::make_pair( COMMAND_ADDSKYSPHERE,&ModeMainGame::OnCommandAddSkySphere ) );
	comand_funcs.insert( std::make_pair( COMMAND_ADDCLEAROBJECT,&ModeMainGame::OnCommandAddClearObject ) );
	comand_funcs.insert( std::make_pair( COMMAND_ADDAREASUPPLY,&ModeMainGame::OnCommandAddAreaSupply ) );
	comand_funcs.insert( std::make_pair( COMMAND_ADDENEMYAAA,&ModeMainGame::OnCommandAddEnemyAAA ) );
	comand_funcs.insert( std::make_pair( COMMAND_ADDAREAENEMYAAA,&ModeMainGame::OnCommandAddAreaEnemyAAA ) );
	comand_funcs.insert( std::make_pair( COMMAND_GAMESTART,&ModeMainGame::OnCommandStart ) );
	comand_funcs.insert( std::make_pair( COMMAND_FEEDIN,&ModeMainGame::OnCommandCrfi ) );
	comand_funcs.insert( std::make_pair( COMMAND_FEEDOUT,&ModeMainGame::OnCommandCrfo ) );
	//comand_funcs.insert( std::make_pair( COMMAND_VE,&ModeMainGame::OnCommandPlayanime ) );
	//comand_funcs.insert( std::make_pair( COMMAND_E,&ModeMainGame::OnCommandScliptend ) );

	while ( !stop_parsing && (now_line >= 0) && (now_line < max_line) )
	{
		const auto script = scripts_data->GetScript( now_line );
		const auto command = (script[0]);
		std::string string_comand{command};
		/*
		bool isThrough = false;

		isThrough = (string_comand == COMMAND_I);
		if ( isThrough == false )
		{
			isThrough = string_comand == COMMAND_IM;
		}

		if ( !isThrough )
		{
			if ( string_comand == COMMAND_W || string_comand == COMMAND_FI || string_comand == COMMAND_FO || string_comand == COMMAND_VE )
			{
				stop_parsing = (this->*comand_funcs[string_comand])(now_line,script);
			}
			else
			{
				(this->*comand_funcs[string_comand])(now_line,script);
			}

			if ( string_comand == COMMAND_A || string_comand == COMMAND_E )
			{
				stop_parsing = true;
			}
		}
		*/
		(this->*comand_funcs[string_comand])(now_line,script);
		if ( string_comand == COMMAND_GAMESTART )
		{
			stop_parsing = true;
			state = ScriptState::GAME;
		}
		++now_line;
	}
	if ( max_line <= dateempty )
	{
		state = ScriptState::EDIT;
	}
}
/**
 *¥fn void ModeGame::Render.
 *¥brief 描画処理毎回呼ばれる
 *¥return void
 */
bool ModeMainGame::Draw()
{
	ModeBase::Draw();
	DrawFormatString( 1000,0,GetColor( 255,255,255 ),"State%d",state );
	_3D_objectServer.Draw( _game,*this );
	switch ( state )
	{
		case ScriptState::EDIT:
			Edit();
			break;

		case ScriptState::PREPARSING:

			break;

		case ScriptState::PARSING:

			break;

		case ScriptState::GAME:
			break;

		case ScriptState::STORY:
			break;

		case ScriptState::RESULT:
			break;

		case ScriptState::CRFEEDIN:
			break;

		case ScriptState::CRFEEDOUT:
			break;

		case ScriptState::LOADING:
			break;

		case ScriptState::END:
			break;
	}
	DrawFeedin( _game );
	DrawFeedout( _game );
	return true;
}
/**
 *¥fn void script_engine::DrawFeedin.
 *¥brief "fi" コマンドによる描画
 *¥return void
 */
void ModeMainGame::DrawFeedin( ApplicationBase& game )const
{
	for ( auto&& crfi : crfi_list )
	{
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,static_cast<int>(_Alpha) );
		DrawBox( 0,0,game.DispSizeW(),game.DispSizeH(),GetColor( crfi->GetRed(),crfi->GetGreen(),crfi->GetBlue() ),TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}
}
/**
 *¥fn void script_engine::DrawFeedout.
 *¥brief "fo" コマンドによる描画
 *¥return void
 */
void ModeMainGame::DrawFeedout( ApplicationBase& game )const
{
	for ( auto&& crfo : crfo_list )
	{
		auto color = GetColor( crfo->GetRed(),crfo->GetGreen(),crfo->GetBlue() );
		auto a = static_cast<int>(_Alpha);
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,a );
		DrawBox( 0,0,game.DispSizeW(),game.DispSizeH(),color,TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}
}