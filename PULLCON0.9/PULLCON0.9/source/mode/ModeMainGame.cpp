/*****************************************************************//**
 * @file   ModeMainGame.cpp
 * @brief  ゲームスクリプト実装
 *
 * @author 阿部健太郎
 * @date   January 2023
 *********************************************************************/

#include "ModeMainGame.h"
#include "ModeTitle.h"
#include "ModeResourceRoad.h"
#include <DxLib.h>
#include "../ApplicationMain.h"
#include "../maingame/Player.h"
#include "../maingame/GameStage.h"
#include "../maingame/SkySphere.h"
#include "../maingame/AreaSupply.h"
#include "../maingame/ClearObject.h"
#include "../maingame/EnemyAAA.h"
#include "../maingame/StageObject.h"
#include "../maingame/AreaEnemySpawn.h"
#include "../maingame/AreaCommunication.h"
#include "../maingame/AreaNoEntry.h"
//#include "ModeSpeakScript.h"
#include "../maingame/EnemyColumn.h"
#include "../maingame/EnemyKobae.h"
#include "ModeSpeakScript.h"

namespace
{
	/** ゲームコマンド */
	const std::string COMMAND_STAGELABEL = "StageLabel";//ステージラベル決定コマンド
	const std::string COMMAND_JUNPLABEL = "StageJump";//ステージジャンプコマンド
	const std::string COMMAND_TURNING = "Turning";//ステージ分岐コマンド
	const std::string COMMAND_GAMESTART = "Start";//ゲームスタート
	const std::string COMMAND_END = "End";//ゲーム終了
	const std::string COMMAND_LOADING = "Load";//ロード画面表示
	const std::string COMMAND_FEEDIN = "CrFeedIn";//フェードイン
	const std::string COMMAND_FEEDOUT = "CrFeedOut";//フェードアウト
	const std::string COMMAND_TIMEWAIT = "TimeWait";//フレーム数待つ
	const std::string COMMAND_STORY = "Story";//ストーリー再生

	const std::string COMMAND_STAGE = "Stage";//ステージ土台決定
	const std::string COMMAND_SKYSPHERE = "SkySphere";//スカイスフィア決定
	const std::string COMMAND_PLAYER = "Player";//位置決定
	const std::string COMMAND_GUNSHIP = "GunShip";//壊したらゲームクリアの位置決定
	const std::string COMMAND_ENEMYAAA = "EnemyAAA";//砲台の単品生成
	const std::string COMMAND_AREAAAA = "AreaAAA";//砲台エリア生成
	const std::string COMMAND_OBJECT = "Object";//ステージ上にオブジェクト追加
	const std::string COMMAND_AREAOBJECT = "AreaObj";//オブジェクトエリア生成
	const std::string COMMAND_ENEMYSPAWN = "AreaSpawn";//敵のスポーンエリアと敵の設定
	const std::string COMMAND_SUPPLY = "Supply";//回復エリアの生成
	const std::string COMMAND_AREACOMMUNICATION = "Communication";//会話エリア発生エリアの設定
	const std::string COMMAND_NOENTRY = "NoEntry";//侵入不能エリア生成



	//編集コマンド
	const std::string ECOMMAND_ADD = "add";//追加コマンド
	const std::string ECOMMAND_DELETE = "delete";//消去コマンド
	const std::string ECOMMAND_CLEAR = "clear";//初期化コマンド
	const std::string ECOMMAND_SAVE = "save";//保存コマンド
	const std::string ECOMMAND_JUNP = "jump";//編集地点変更コマンド
	//文字列分割用
	const std::string DELIMITER = ",";
	//jsonファイル関係
	const std::string FILENAME = "pullcon0.9.json";//ファイル名
	const std::string FILEPASS = "res/script/gamescript/" + FILENAME;//ファイルパス
	const std::string GAMESCRIPT = "pullcon0.9";//スクリプト名
}

/**
 * @fn void ModeMainGame::ModeMainGame.
 * @brief コンストラクタ
 * @param game ApplicationMainの参照を受け取る
 * @param layer 何番目に移すか
 * @return void
 */
ModeMainGame::ModeMainGame( ApplicationBase& game,int layer )
	: ModeBase( game,layer )
{
	scripts_data = std::make_unique<ScriptsData>();
	Initialize( FILEPASS,GAMESCRIPT,FILENAME );

	///////////////////////////////////////////////////////
	_cg = ResourceServer::LoadGraph( "res/cursor00.png" );
	_se = ResourceServer::LoadSoundMem( "res/sound/stage1~3 BGM/650832__timbre__weasel-damage-excerpt-of-audiomirages-freesound-647499.wav" );
	ChangeVolumeSoundMem( 255 * 40 / 100,_se );
	//PlaySoundMem(_se, DX_PLAYTYPE_LOOP);
	// デフォルトのフォントで、サイズ４０、太さ３のフォントを作成し
	// 作成したデータの識別番号を変数 FontHandle に保存する
	_handlefont = CreateFontToHandle( NULL,40,3 );
	_vCursor = {0.0f, 0.0f, 0.0f};
	_clear = false;
	_dbgCollisionDraw = false;
	_transparence = false;
	///////////////////////////////////////////////////////
}
/**
 * @fn void ModeMainGame::~ModeMainGame.
 * @brief デストラクタ 後処理を行う
 * @return void
 */
ModeMainGame::~ModeMainGame()
{
	Destroy();
}
/**
 * @fn void ModeMainGame::Destroy.
 * @brief 後処理をまとめた関数
 * @return void
 */
void ModeMainGame::Destroy()
{
	/** stateをPREPARSINGにしておく */
	state = ScriptState::PREPARSING;
#if _DEBUG
	scripts_data->WriteJson( FILENAME,GAMESCRIPT );
#endif
	max_line = 0;
	now_line = 0;
	wait_count = 0;
	scripts_data.reset();
	label_list.clear();
	crfi_list.clear();
	crfo_list.clear();
	scripts_data = nullptr;
}

void ModeMainGame::Initialize( std::string jsonpath,std::string scriptsname,std::string jsonname )
{
	ModeBase::Initialize();
	state = ScriptState::PREPARSING;
	start_time = 0;
	max_line = 0;
	now_line = 0;
	feedcount = 0.0;
	alpha = 0;
	is_notcant = false;
	is_notcommand = false;
	is_cannotdelete = false;

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

	return;
};
/**
 * @fn void ModeMainGame::PreParsing.
 * @brief 事前呼び込み
 * ステージラベルを呼び込みどこに何があるか保存
 * @return void
 */
void ModeMainGame::PreParsing()
{
	FunctionGameCommand comand_funcs;
	comand_funcs.insert( std::make_pair( COMMAND_STAGELABEL,&ModeMainGame::OnCommandStageLabel ) );
	auto script = scripts_data->GetScript( now_line,DELIMITER );

	std::string game_comand{script[0]};

	if ( game_comand == COMMAND_STAGELABEL )
	{
		(this->*comand_funcs[game_comand])(now_line,script);
	}

	++now_line;

	if ( now_line >= max_line )
	{
		now_line = 0;
		state = ScriptState::PARSING;
	}
}
/**
 * @fn void ModeMainGame::Parsing.
 * @brief
 * @return void
 */
void ModeMainGame::Parsing()
{
	object_main_game.Clear();
	auto stop_parsing = false;
	unsigned	int date_empty = 0;
	FunctionGameCommand comand_funcs;
	comand_funcs.insert( std::make_pair( COMMAND_JUNPLABEL,&ModeMainGame::OnCommandJumpLabel ) );
	comand_funcs.insert( std::make_pair( COMMAND_TURNING,&ModeMainGame::OnCommandTurning ) );
	comand_funcs.insert( std::make_pair( COMMAND_GAMESTART,&ModeMainGame::OnCommandStart ) );
	comand_funcs.insert( std::make_pair( COMMAND_END,&ModeMainGame::OnCommandEnd ) );
	comand_funcs.insert( std::make_pair( COMMAND_LOADING,&ModeMainGame::OnCommandLoading ) );
	comand_funcs.insert( std::make_pair( COMMAND_FEEDIN,&ModeMainGame::OnCommandCrFeedIn ) );
	comand_funcs.insert( std::make_pair( COMMAND_FEEDOUT,&ModeMainGame::OnCommandCrFeedOut ) );
	comand_funcs.insert( std::make_pair( COMMAND_TIMEWAIT,&ModeMainGame::OnCommandTimeWait ) );
	comand_funcs.insert( std::make_pair( COMMAND_STORY,&ModeMainGame::OnCommandStory ) );
	comand_funcs.insert( std::make_pair( COMMAND_STAGE,&ModeMainGame::OnCommandStage ) );
	comand_funcs.insert( std::make_pair( COMMAND_SKYSPHERE,&ModeMainGame::OnCommandSkySphere ) );
	comand_funcs.insert( std::make_pair( COMMAND_PLAYER,&ModeMainGame::OnCommandPLayer ) );
	comand_funcs.insert( std::make_pair( COMMAND_GUNSHIP,&ModeMainGame::OnCommandGunShip ) );
	comand_funcs.insert( std::make_pair( COMMAND_ENEMYAAA,&ModeMainGame::OnCommandEnemyAAA ) );
	comand_funcs.insert( std::make_pair( COMMAND_AREAAAA,&ModeMainGame::OnCommandAreaAAA ) );
	comand_funcs.insert( std::make_pair( COMMAND_OBJECT,&ModeMainGame::OnCommandObject ) );
	comand_funcs.insert( std::make_pair( COMMAND_AREAOBJECT,&ModeMainGame::OnCommandAreaObj ) );
	comand_funcs.insert( std::make_pair( COMMAND_ENEMYSPAWN,&ModeMainGame::OnCommandAreaSpawn ) );
	comand_funcs.insert( std::make_pair( COMMAND_SUPPLY,&ModeMainGame::OnCommandSupply ) );
	comand_funcs.insert( std::make_pair( COMMAND_AREACOMMUNICATION,&ModeMainGame::OnCommandCommunication ) );
	comand_funcs.insert( std::make_pair( COMMAND_NOENTRY,&ModeMainGame::OnCommandNoEntry ) );

	///////////////////////////////////////////////////////
	auto column = std::make_shared<EnemyColumn>( _game,*this );
	GetObjectServer3D().Add( column );
	auto kobae = std::make_shared<EnemyKobae>( _game,*this );
	GetObjectServer3D().Add( kobae );
	///////////////////////////////////////////////////////

	while ( !(stop_parsing) && (now_line >= 0) && (now_line < max_line) )
	{
		auto script = scripts_data->GetScript( now_line,DELIMITER );
		const auto& command = (script[0]);
		std::string string_comand{command};

		if ( string_comand == COMMAND_STAGELABEL )
		{
			++now_line;
		}
		else
		{
			if ( string_comand == COMMAND_LOADING ||
					 string_comand == COMMAND_GAMESTART ||
					 string_comand == COMMAND_FEEDIN ||
					 string_comand == COMMAND_FEEDOUT ||
					 string_comand == COMMAND_TIMEWAIT ||
					 string_comand == COMMAND_STORY )
			{
				stop_parsing = (this->*comand_funcs[string_comand])(now_line,script);
			}
			else
			{
				(this->*comand_funcs[string_comand])(now_line,script);
			}

			if ( string_comand == COMMAND_GAMESTART )
			{
				state = ScriptState::EDIT;
			}
			++now_line;
		}
	}
#if _DEBUG
	if ( now_line >= max_line )
	{
		state = ScriptState::EDIT;
	}
#endif
}

bool ModeMainGame::Update()
{
	ModeBase::Update();
	object_main_game.Update();
	ui_player.Update();
	if ( _game.Getinput().XinputEveryOtherLeftTrigger( 30 ) )
	{
		_dbgCollisionDraw = !_dbgCollisionDraw;
	}


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

		case ScriptState::LOADING:
			break;

		case ScriptState::END:
			auto title = std::make_unique<ModeTitle>( _game,1 );
			_game.GetInstance()->GetModeServer()->Add( std::move( title ) );
			_game.GetModeServer()->Del( *this );
			break;
	}


	return true;
}

void ModeMainGame::CrfiUpdate()
{
	auto i = 255 / feedcount;


	if ( alpha > 0.0 )
	{
		alpha -= i;
	}
	else
	{
		alpha = 0.0;
		state = ScriptState::PARSING;
	}
}

void ModeMainGame::CrfoUpdate()
{
	auto i = 255.0f / feedcount;


	if ( alpha < 255.0 )
	{
		alpha += i;
	}
	else
	{
		alpha = 255.0;
		state = ScriptState::PARSING;
	}
}

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

bool ModeMainGame::GetLineNumber( const std::string& str,unsigned int& line ) const
{
	for ( auto&& label : label_list )
	{
		if ( label->GetLabel() == str )
		{
			line = label->GetLineNumber();

			return true;
		}
	}

	return false;
}

bool ModeMainGame::OnCommandStageLabel( unsigned int line,std::vector<std::string>& scripts )
{
	bool result = false;
	if ( state != ScriptState::EDIT )
	{
		auto label = std::make_unique<CommandLabel>( line,scripts );

		if ( !label->Check() )
		{
			return result;
		}

		label_list.emplace_back( std::move( label ) );
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,1 > input_str =
		{
			"ステージ名の入力"
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};
/**
 * @fn bool ModeMainGame::OnCommandJunpLabel.
 * @brief ジャンプコマンド関数
 * @param line 行数
 * @param scripts スクリプトの中身
 * @return bool 成功可否(true成功、false失敗)
 */
bool ModeMainGame::OnCommandJumpLabel( unsigned int line,std::vector<std::string>& scripts )
{
	/** 引数として持ってきたlineのコピーを0初期化 */
	line = 0U;
	bool result = false;
	if ( state != ScriptState::EDIT )
	{
		/** 成功可否(true成功、false失敗)を取得、lineにラベルコマンドで追加した文字列に対応した行数を入れる */
		result = GetLineNumber( scripts[1],line );
		/** 成功した場合naw_lineにlineをいれジャンプする */
		if ( result )
		{
			now_line = line;
		}
		return result;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,1 > input_str =
		{
			"ジャンプ先のステージ名"
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};

bool ModeMainGame::OnCommandTurning( unsigned int line,std::vector<std::string>& scripts )
{
	auto result = false;
	if ( state != ScriptState::EDIT )
	{
		int clear_time = (GetNowCount() - start_time) / 1000;
		int turning_time = 0;

		line = 0U;
		if ( !GetLineNumber( scripts[1],line ) )
		{
			return result;
		};
		if ( !(string::ToInt( scripts[2],turning_time )) )
		{
			return result;
		}
		if ( clear_time < turning_time )
		{
			now_line = line;
		}
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,2 > input_str =
		{
			"ステージ名",
			"クリア秒数(この秒数以下だとそこのステージにいく)"
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};

bool ModeMainGame::OnCommandStart( unsigned int line,std::vector<std::string>& scripts )
{
	if ( state != ScriptState::EDIT )
	{
		const size_t SCRIPTSIZE = 2;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return false;
		}
		/* 現在経過時間を得る */
		start_time = GetNowCount();
		state = ScriptState::GAME;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return false;
		}
	}
	return true;
};

bool ModeMainGame::OnCommandEnd( unsigned int line,std::vector<std::string>& scripts )
{
	if ( state != ScriptState::EDIT )
	{
		const size_t SCRIPTSIZE = 2;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return false;
		}

		state = ScriptState::END;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return false;
		}
	}
	return true;
};

bool ModeMainGame::OnCommandLoading( unsigned int line,std::vector<std::string>& scripts )
{
	if ( state != ScriptState::EDIT )
	{
		const size_t SCRIPTSIZE = 2;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return false;
		}
		state = ScriptState::LOADING;
		auto loading = std::make_unique<ModeResourceRoad>( _game,20 );
		_game.GetModeServer()->Add( std::move( loading ) );
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return false;
		}
	}
	return true;
};

bool ModeMainGame::OnCommandCrFeedIn( unsigned int line,std::vector<std::string>& scripts )
{
	crfi_list.clear();
	auto result = false;
	if ( state != ScriptState::EDIT )
	{
		auto crfi = std::make_unique<CommandCrFeedIn>( line,scripts );
		if ( !crfi->Check() )
		{
			return result;
		}
		feedcount = static_cast<float>(crfi->GetinCount());
		crfi_list.emplace_back( std::move( crfi ) );
		alpha = 255.0;
		state = ScriptState::CRFEEDIN;
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,4 > input_str =
		{
			"フレーム数(消えるまでの時間)",
			"赤の色段階(0~255)",
			"緑の色段階(0~255)",
			"青の色段階(0~255)"
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}

	return  result;
}

bool ModeMainGame::OnCommandCrFeedOut( unsigned int line,std::vector<std::string>& scripts )
{
	crfo_list.clear();
	auto result = false;
	if ( state != ScriptState::EDIT )
	{
		auto crfo = std::make_unique<CommandCrFeedOut>( line,scripts );
		if ( !crfo->Check() )
		{
			return result;
		}
		feedcount = static_cast<float>(crfo->GetoutCount());
		crfo_list.emplace_back( std::move( crfo ) );
		alpha = 0.0;
		state = ScriptState::CRFEEDOUT;
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,4 > input_str =
		{
			"フレーム数(消えるまでの時間)",
			"赤の色段階(0~255)",
			"緑の色段階(0~255)",
			"青の色段階(0~255)"
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};

bool ModeMainGame::OnCommandTimeWait( unsigned int line,std::vector<std::string>& scripts )
{
	auto result = false;
	if ( state != ScriptState::EDIT )
	{
		auto wait = 0;
		const size_t SCRIPTSIZE = 2;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}

		if ( string::ToInt( scripts[1],wait ) )
		{
			wait_count = static_cast<unsigned int>(wait);
			state = ScriptState::TIME_WAIT;
			result = true;
		}
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,1 > input_str =
		{
			"フレーム数の入力",
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};

bool ModeMainGame::OnCommandStory( unsigned int line,std::vector<std::string>& scripts )
{
	bool result = false;
	if ( state != ScriptState::EDIT )
	{
		const size_t SCRIPTSIZE = 3;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		auto story = std::make_unique<ModeSpeakScript>( _game,30,scripts[1] );
		_game.GetModeServer()->Add( std::move( story ) );
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,2 > input_str =
		{
			"ストーリーid(ファイル名/ストーリー名)"
			"ゲームを止めるか(1:止める0:止めない)"
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};
/**
 * @fn bool ModeMainGame::OnCommandStage.
 * @brief ステージ土台追加コマンド
 * @param line 今の行
 * @param scripts スクリプトの中身
 * @return bool 成功可否(true成功、false失敗)
 */
bool ModeMainGame::OnCommandStage( unsigned int line,std::vector<std::string>& scripts )
{
	bool result = false;
	if ( state != ScriptState::EDIT )
	{
		const size_t SCRIPTSIZE = 2;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		int object_id = 0;
		if ( !(string::ToInt( scripts[1],object_id )) )
		{
			return result;
		};
		auto stage = std::make_shared<GameStage>( _game,*this,object_id );
		object_main_game.Add( stage );
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,1 > input_str =
		{
			"オブジェクトid(企画書参照)を記入してください",
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};

bool ModeMainGame::OnCommandSkySphere( unsigned int line,std::vector<std::string>& scripts )
{
	bool result = false;
	if ( state != ScriptState::EDIT )
	{
		const size_t SCRIPTSIZE = 2;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		int object_id = 0;
		if ( !(string::ToInt( scripts[1],object_id )) )
		{
			return result;
		};

		auto skysphere = std::make_shared<SkySphere>( _game,*this,object_id );
		object_main_game.Add( skysphere );
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,1 > input_str =
		{
			"オブジェクトid(企画書参照)を記入してください",
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};

bool ModeMainGame::OnCommandPLayer( unsigned int line,std::vector<std::string>& scripts )
{
	bool result = false;
	if ( state != ScriptState::EDIT )
	{
		vector4 posi;
		float scale = 1.0f;
		float speed = 30.0f;
		const size_t SCRIPTSIZE = 6;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		if ( !IsSetVrctor4( posi,scripts ) )
		{
			return result;
		}
		if ( !(string::ToFloat( scripts[4],scale )) )
		{
			return result;
		}
		if ( scale <= 0.0f )
		{
			return result;
		}
		if ( !(string::ToFloat( scripts[5],speed )) )
		{
			return result;
		}
		auto fuel_gage = std::make_unique<UIFuelGage>( _game,0,*this );
		ui_player.Add( std::move( fuel_gage ) );
		auto hp_gage = std::make_unique<UIHpGage>( _game,0,*this );
		ui_player.Add( std::move( hp_gage ) );
		auto player = std::make_shared<Player>( _game,*this );
		player->SetPosition( posi );
		player->SetScale( scale );
		player->SetSpeed( speed );
		object_main_game.Add( player );
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,5 > input_str =
		{
			"x座標を入力してください",
			"y座標を入力してください",
			"z座標を入力してください",
			"大きさを入力してください",
			"速さを入力してください"
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}

	return result;
};

bool ModeMainGame::OnCommandGunShip( unsigned int line,std::vector<std::string>& scripts )
{
	bool result = false;
	if ( state != ScriptState::EDIT )
	{
		vector4 posi;
		float radius = 0.0f;
		float scale = 1.0f;
		const size_t SCRIPTSIZE = 6;

		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		if ( !IsSetVrctor4( posi,scripts ) )
		{
			return result;
		}
		if ( !(string::ToFloat( scripts[4],scale )) )
		{
			return result;
		}
		if ( !(string::ToFloat( scripts[5],radius )) )
		{
			return result;
		}
		auto clearobject = std::make_shared<ClearObject>( _game,*this,radius );
		clearobject->SetPosition( posi );
		clearobject->SetScale( scale );
		object_main_game.Add( clearobject );
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,5 > input_str =
		{
			"x座標を入力してください",
			"y座標を入力してください",
			"z座標を入力してください",
			"大きさを入力してください",
			"半径を入力してください"
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};

bool ModeMainGame::OnCommandEnemyAAA( unsigned int line,std::vector<std::string>& scripts )
{
	bool result = false;
	if ( state != ScriptState::EDIT )
	{
		vector4 posi;
		int object_min_id = 0;
		int object_max_id = 0;
		float scale = 1.0f;
		float y_rad = 0.0f;
		float x_rad = 0.0f;
		int pile_num = 0;
		int pile_min_num = 0;
		int pile_max_num = 0;
		int aim_player = 0;
		const size_t SCRIPTSIZE = 12;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}

		if ( !IsSetVrctor4( posi,scripts ) )
		{
			return result;
		}

		/** 文字列をスケールに変換 */
		if ( !(string::ToFloat( scripts[4],scale )) )
		{
			return result;
		}
		/** scaleが0以下だったら返す */
		if ( scale <= 0.0f )
		{
			return result;
		}
		/** 砲台が生成されるときランダムに生成されるため、あらかじめ決めておいた呼び込む砲台のidの最低値 */
		if ( !(string::ToInt( scripts[5],object_min_id )) )
		{
			return result;
		};
		/** 砲台が生成されるときランダムに生成されるため、あらかじめ決めておいた呼び込む砲台のidの最高値 */
		if ( !(string::ToInt( scripts[6],object_max_id )) )
		{
			return result;
		};
		/** y軸砲台の傾きの初期位置 */
		if ( !(string::ToFloat( scripts[7],y_rad )) )
		{
			return result;
		}
		/** z軸砲台の傾きの初期位置 */
		if ( !(string::ToFloat( scripts[8],x_rad )) )
		{
			return result;
		}
		/** 下に重なる砲台の個数の最低値 */
		if ( !(string::ToInt( scripts[9],pile_min_num )) )
		{
			return result;
		}
		/** 下に重なる砲台の個数の最高値 */
		if ( !(string::ToInt( scripts[10],pile_max_num )) )
		{
			return result;
		}
		/** ランダム値取得 */
		pile_num = utility::get_random( pile_min_num,pile_max_num );
		if ( !(string::ToInt( scripts[11],aim_player )) )
		{
			return result;
		}
		auto enemyAAA = std::make_shared<EnemyAAA>( _game,*this,object_min_id,object_max_id,pile_num,posi );

		enemyAAA->SetScale( scale );
		enemyAAA->SetAxialX( x_rad );
		enemyAAA->SetAxialY( y_rad );
		enemyAAA->SetType( aim_player );
		object_main_game.Add( enemyAAA );
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,11 > input_str =
		{
		"x座標",
		"y座標",
		"z座標",
		"スケール",
		"オブジェクトid最低値(番号)",
		"オブジェクトid最高値(番号)",
		"y軸角度(0.0~360.0度(左回り))",
		"x軸(0.0~40.0度)",
		"下に重なっている対空砲の最小値",
		"下に重なっている対空砲の最大数",
		"プレイヤーを狙うか(0:狙う; 1:狙わない)"
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};

bool ModeMainGame::OnCommandAreaAAA( unsigned int line,std::vector<std::string>& scripts )
{
	bool result = false;
	if ( state != ScriptState::EDIT )
	{
		/** エリアのポジション */
		vector4 posi;
		/** scriptsの中の想定している数値や文字列の数 */
		const size_t SCRIPTSIZE = 14;
		/** ポジションからの最大の距離 */
		float range = 0.0f;
		/** 大きさ */
		float scale = 1.0f;
		/** オブジェクト同士の最低の距離 */
		float interval = 0.0f;
		/** あらかじめ決めていた対空砲の順番の一番低いid */
		int object_min_id = 0;
		/** あらかじめ決めていた対空砲の順番の一番高いid */
		int object_max_id = 0;
		/** AAA下に続く最低の数 */
		int pile_min_num = 0;
		/** AAA下に続く最高の数 */
		int pile_max_num = 0;
		/** マップにエリア表示する為の赤色の段階番号 */
		int min_map_draw_red = 0;
		/** マップにエリア表示する為の緑色の段階番号 */
		int min_map_draw_green = 0;
		/** マップにエリア表示する為の青色の段階番号 */
		int min_map_draw_blue = 0;

		/** scriptsの中に指定のサイズ入っているか確認入ってない場合失敗を返す */
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}

		/** ポジションを文字列からxyzを取得。うまく変換出来なかった場合失敗を返す */
		if ( !IsSetVrctor4( posi,scripts ) )
		{
			return result;
		}

		/** 大きさを文字列から取得。うまく変換出来なかった場合失敗を返す */
		if ( !(string::ToFloat( scripts[4],scale )) )
		{
			return result;
		}
		/** scaleが0以下だった場合失敗を返す */
		if ( scale <= 0.0f )
		{
			return result;
		}
		/** 対空砲の一番低いidを文字列から取得。うまく変換出来なかった場合失敗を返す */
		if ( !(string::ToInt( scripts[5],object_min_id )) )
		{
			return result;
		};
		/** 対空砲の一番高いidを文字列から取得。うまく変換出来なかった場合失敗を返す */
		if ( !(string::ToInt( scripts[6],object_max_id )) )
		{
			return result;
		};
		/** ポジションからの最大の距離を文字列から取得。うまく変換出来なかった場合失敗を返す */
		if ( !(string::ToFloat( scripts[7],range )) )
		{
			return result;
		}
		/** オブジェクト同士の最低の距離を文字列から取得。うまく変換出来なかった場合失敗を返す */
		if ( !(string::ToFloat( scripts[8],interval )) )
		{
			return result;
		}
		/** AAA下に続く最低の数を文字列から取得。うまく変換出来なかった場合失敗を返す */
		if ( !(string::ToInt( scripts[9],pile_min_num )) )
		{
			/** pile_min_numが0未満だった場合失敗を返す */
			if ( pile_min_num < 0 )
			{
				return result;
			}
			return result;
		}
		/** AAA下に続く最高の数を文字列から取得。うまく変換出来なかった場合失敗を返す */
		if ( !(string::ToInt( scripts[10],pile_max_num )) )
		{
			/** pile_max_numが0未満だった場合失敗を返す */
			if ( pile_max_num < 0 )
			{
				return result;
			}
			return result;
		}
		/**  */
		if ( !(string::ToInt( scripts[11],min_map_draw_red )) )
		{
			return result;
		}
		if ( !(string::ToInt( scripts[12],min_map_draw_green )) )
		{
			return result;
		}
		if ( !(string::ToInt( scripts[13],min_map_draw_blue )) )
		{
			return result;
		}
		auto color = GetColor( min_map_draw_red,min_map_draw_green,min_map_draw_blue );

		std::vector<std::tuple<math::vector4,int>>posivec;
		int num_while = 0;
		auto x_posi_max = posi.x + std::abs( range );
		auto x_posi_min = posi.x - std::abs( range );
		auto z_posi_max = posi.z + std::abs( range );
		auto z_posi_min = posi.z - std::abs( range );
		while ( true )
		{
			auto posi_rand_x = static_cast<float>(utility::get_random( static_cast<int>(x_posi_min),static_cast<int>(x_posi_max) ));
			auto posi_rand_z = static_cast<float>(utility::get_random( static_cast<int>(z_posi_min),static_cast<int>(z_posi_max) ));
			int pile_num = utility::get_random( pile_min_num,pile_max_num );
			vector4 rand_posi = {posi_rand_x,posi.y,posi_rand_z};

			int in_range_nim = 0;

			for ( auto&& set_pos : posivec )
			{
				auto pos = std::get<0>( set_pos ) - rand_posi;
				if ( pos.Lenght() < interval )
				{
					in_range_nim++;
					break;
				}
			}

			if ( num_while > 100 )
			{
				break;
			}
			num_while++;
			if ( in_range_nim > 0 )
			{
				continue;
			}

			auto pos = rand_posi - posi;
			if ( pos.Lenght() > range )
			{
				continue;
			}

			posivec.push_back( std::make_tuple( rand_posi,pile_num ) );
		}



		for ( auto&& set_pos : posivec )
		{
			auto enemyAAA = std::make_shared<EnemyAAA>( _game,*this,object_min_id,object_max_id,std::get<1>( set_pos ),std::get<0>( set_pos ) );

			enemyAAA->SetScale( scale );
			object_main_game.Add( enemyAAA );
		}
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,13 > input_str =
		{
			"x座標",
			"y座標",
			"z座標",
			"スケール",
			"オブジェクトid最低値(番号)",
			"オブジェクトid最高値(番号)",
			"円の範囲",
			"対空砲の間隔",
			"下に重なっている対空砲の最小値",
			"下に重なっている対空砲の最大値",
			"map赤の色段階",
			"map緑の色段階",
			"map青の色段階"
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};

bool ModeMainGame::OnCommandObject( unsigned int line,std::vector<std::string>& scripts )
{
	bool result = false;
	if ( state != ScriptState::EDIT )
	{
		vector4 posi;
		float scale = 1.0f;
		int object_id = 0;
		int collision_id = 1;
		float radius = 0.0f;
		const size_t SCRIPTSIZE = 8;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}

		if ( !IsSetVrctor4( posi,scripts ) )
		{
			return result;
		}

		if ( !(string::ToFloat( scripts[4],scale )) )
		{
			return result;
		}
		if ( scale <= 0.0f )
		{
			return result;
		}
		if ( !(string::ToFloat( scripts[5],radius )) )
		{
			return result;
		};
		if ( !(string::ToInt( scripts[6],object_id )) )
		{
			return result;
		};
		if ( !(string::ToInt( scripts[7],collision_id )) )
		{
			return result;
		};

		auto object = std::make_shared<StageObject>( _game,*this,object_id,collision_id );
		object->SetPosition( posi );
		object->SetScale( scale );
		object->SetCollisionRadius( radius );
		//object->SetCollision( posi,radius );
		object_main_game.Add( object );
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,7 > input_str =
		{
			"x座標",
			"y座標",
			"z座標",
			"スケール",
			"当たり判定球の半径",
			"オブジェクトid(番号)",
			"コリジョン有無(1有; 0無)"

		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};

bool ModeMainGame::OnCommandAreaObj( unsigned int line,std::vector<std::string>& scripts )
{
	bool result = false;
	if ( state != ScriptState::EDIT )
	{
		/** エリアのポジション */
		vector4 posi;
		/** scriptsの中にある数値や文字列の数 */
		const size_t SCRIPTSIZE = 11;
		/** 大きさ */
		float scale = 1.0f;
		/**  */
		float radius = 1.0f;
		/** 配置するものの範囲 */
		float range = 0.0f;
		/** 配置するものの間隔 */
		float interval = 0.0f;
		/** 呼び込む3dモデルのid */
		int object_id = 0;
		/** コリジョン有無(1有;0無) */
		int collision_id = 1;
		/** 円状に配置か正方形状に配置か。1円状,0正方形状 */
		int is_circular = 0;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}

		if ( !IsSetVrctor4( posi,scripts ) )
		{
			return result;
		}

		if ( !(string::ToFloat( scripts[4],scale )) )
		{
			return result;
		}
		if ( scale <= 0.0f )
		{
			return result;
		}
		if ( !(string::ToFloat( scripts[5],radius )) )
		{
			return result;
		};
		if ( !(string::ToInt( scripts[6],object_id )) )
		{
			return result;
		};
		if ( !(string::ToInt( scripts[7],collision_id )) )
		{
			return result;
		};
		if ( !(string::ToInt( scripts[8],is_circular )) )
		{
			return result;
		};
		if ( !(string::ToFloat( scripts[9],range )) )
		{
			return result;
		}
		if ( !(string::ToFloat( scripts[10],interval )) )
		{
			return result;
		}

		std::vector<math::vector4>posivec;
		int num_while = 0;
		auto x_posi_max = posi.x + std::abs( range );
		auto x_posi_min = posi.x - std::abs( range );
		auto z_posi_max = posi.z + std::abs( range );
		auto z_posi_min = posi.z - std::abs( range );
		while ( true )
		{
			auto posi_rand_x = static_cast<float>(utility::get_random( static_cast<int>(x_posi_min),static_cast<int>(x_posi_max) ));
			auto posi_rand_z = static_cast<float>(utility::get_random( static_cast<int>(z_posi_min),static_cast<int>(z_posi_max) ));

			vector4 rand_posi = {posi_rand_x,posi.y,posi_rand_z};

			int in_range_nim = 0;

			for ( auto&& set_pos : posivec )
			{
				auto pos = set_pos - rand_posi;
				if ( pos.Lenght() < interval )
				{
					in_range_nim++;
				}
			}

			if ( num_while > 100 )
			{
				break;
			}
			num_while++;
			if ( in_range_nim > 0 )
			{
				continue;
			}

			auto pos = rand_posi - posi;
			if ( is_circular )
			{
				if ( pos.Lenght() > range )
				{
					continue;
				}
			}
			posivec.push_back( rand_posi );
		}

		for ( auto&& set_pos : posivec )
		{
			auto object = std::make_shared<StageObject>( _game,*this,object_id,collision_id );
			object->SetPosition( set_pos );
			object->SetScale( scale );
			object->SetCollision( set_pos,radius );
			object_main_game.Add( object );
		}
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,10 > input_str =
		{
			"x座標",
			"y座標",
			"z座標",
			"スケール",
			"当たり判定球の半径",
			"オブジェクトid(番号)",
			"コリジョン有無(1有;0無)",
			"円か四角選択(1円;0四角)",
			"円の範囲",
			"オブジェクトの間隔"
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}

	return result;
};

bool ModeMainGame::OnCommandAreaSpawn( unsigned int line,std::vector<std::string>& scripts )
{
	bool result = false;
	if ( state != ScriptState::EDIT )
	{
		vector4 posi;
		int spawn_id = 0;
		int spawn_fream = 0;
		const size_t SCRIPTSIZE = 6;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}

		if ( !IsSetVrctor4( posi,scripts ) )
		{
			return result;
		}

		if ( !(string::ToInt( scripts[4],spawn_fream )) )
		{
			return result;
		};
		if ( !(string::ToInt( scripts[5],spawn_id )) )
		{
			return result;
		};
		auto spawn_eria = std::make_shared<AreaEnemySpawn>( _game,*this,spawn_fream,spawn_id );
		spawn_eria->SetPosition( posi );
		object_main_game.Add( spawn_eria );
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,5> input_str =
		{
			"x座標",
			"y座標",
			"z座標",
			"スポーン間隔(フレーム数)",
			"敵の種類(1スカイハンターズ; 2コバエーズ; 3両方)"

		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};

bool ModeMainGame::OnCommandSupply( unsigned int line,std::vector<std::string>& scripts )
{
	bool result = false;
	if ( state != ScriptState::EDIT )
	{
		vector4 posi;
		float radius = 0.0f;
		const size_t SCRIPTSIZE = 5;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}

		if ( !IsSetVrctor4( posi,scripts ) )
		{
			return result;
		}

		if ( !(string::ToFloat( scripts[4],radius )) )
		{
			return result;
		}
		auto supplyeria = std::make_shared<AreaSupply>( _game,*this,radius );
		supplyeria->SetPosition( posi );
		object_main_game.Add( supplyeria );
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,4> input_str =
		{
			"x座標",
			"y座標",
			"z座標",
			"球の半径"
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};

bool ModeMainGame::OnCommandCommunication( unsigned int line,std::vector<std::string>& scripts )
{
	bool result = false;
	if ( state != ScriptState::EDIT )
	{
		vector4 posi;
		float radius = 0.0f;

		const size_t SCRIPTSIZE = 6;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		if ( !IsSetVrctor4( posi,scripts ) )
		{
			return result;
		};

		if ( !(string::ToFloat( scripts[4],radius )) )
		{
			return result;
		}

		auto commu_aria = std::make_shared<AreaCommunication>( _game,*this,scripts[5] );
		commu_aria->SetPosition( posi );
		commu_aria->SetCollision( posi,radius );
		object_main_game.Add( commu_aria );
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,5> input_str =
		{
			"x座標",
			"y座標",
			"z座標",
			"球の半径",
			"ストーリーid(ファイル名/ストーリー名)"
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};

bool ModeMainGame::OnCommandNoEntry( unsigned int line,std::vector<std::string>& scripts )
{
	bool result = false;
	if ( state != ScriptState::EDIT )
	{
		vector4 posi;
		float radius = 0.0f;
		const size_t SCRIPTSIZE = 5;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}

		if ( !IsSetVrctor4( posi,scripts ) )
		{
			return result;
		};

		if ( !(string::ToFloat( scripts[4],radius )) )
		{
			return result;
		}

		auto no_entry = std::make_shared<AreaNoEntry>( _game,*this );
		no_entry->SetPosition( posi );
		no_entry->SetCollisionRadius( radius );
		object_main_game.Add( no_entry );
		result = true;
	}
	else
	{
		const size_t SCRIPTSIZE = 1;
		if ( scripts.size() != SCRIPTSIZE )
		{
			return result;
		}
		std::array < std::string,4> input_str =
		{
			"x座標",
			"y座標",
			"z座標",
			"球の半径"
		};
		result = true;
		for ( int i = 0; i < input_str.size(); i++ )
		{
			if ( !CommandInputString( 0,0,input_str[i],scripts ) )
			{
				result = false;
				break;
			};
		}
	}
	return result;
};

bool ModeMainGame::IsSetVrctor4( math::vector4& set,std::vector<std::string>& scripts )
{
	if ( !(string::ToFloat( scripts[1],set.x )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[2],set.y )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[3],set.z )) )
	{
		return false;
	}

	return true;
};

bool ModeMainGame::Draw()
{
	ModeBase::Draw();
	object_main_game.Draw();
	ui_player.Draw();
	DrawFormatString( 1000,0,GetColor( 255,255,255 ),"State%d",state );
	DrawBox( 0,100,_iFuel * 2,140,GetColor( 255,0,0 ),TRUE );
	/////////////////////////////////////////////////////////////////////////////
	if ( _clear )
	{
// 作成したフォントで画面左上に『CLEAR』と黄色の文字列を描画する
		DrawStringToHandle( _game.DispSizeW() / 2,_game.DispSizeH() / 2,"C L E A R!!",GetColor( 255,255,0 ),_handlefont );
	}
	if ( !_transparence )
	{
		VECTOR ScreenPos = ConvWorldPosToScreenPos( ToDX( _vCursor ) );
		DrawRotaGraph( static_cast<int>(ScreenPos.x),static_cast<int>(ScreenPos.y),0.5,0,_cg,TRUE );
	}
	//////////////////////////////////////////////////////////////////////////////
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
			DrawFeedIn();
			break;

		case ScriptState::CRFEEDOUT:
			DrawFeedOut();
			break;

		case ScriptState::LOADING:
			break;

		case ScriptState::END:
			break;
	}


	return true;
}

bool ModeMainGame::DebugDraw()
{
	ModeBase::DebugDraw();
	math::vector4 posi;

	for ( auto&& obj : object_main_game.GetObjects() )
	{
		if ( obj->GetType() == ActorBase3D::Type::kPlayer )
		{
			posi = obj->GetPosition();
		}
	}
	int x = 0,y = 500,size = 16;
	DrawFormatString( x,y,GetColor( 255,0,0 ),"  pos    = (%5.2f, %5.2f, %5.2f)",posi.x,posi.y,posi.z );

	return true;
};

void ModeMainGame::DrawFeedIn()const
{
	for ( auto&& crfi : crfi_list )
	{
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,static_cast<int>(alpha) );
		DrawBox( 0,0,_game.DispSizeW(),_game.DispSizeH(),GetColor( crfi->GetRed(),crfi->GetGreen(),crfi->GetBlue() ),TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}
}

void ModeMainGame::DrawFeedOut()const
{
	for ( auto&& crfo : crfo_list )
	{
		auto color = GetColor( crfo->GetRed(),crfo->GetGreen(),crfo->GetBlue() );
		auto a = static_cast<int>(alpha);
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,a );
		DrawBox( 0,0,_game.DispSizeW(),_game.DispSizeH(),color,TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}
}
/**
 * @fn void ModeMainGame::Edit.
 * @brief エディットモードの時の描画、入力処理
 * @return void
 */
void ModeMainGame::Edit()
{
	const int NONE = 0;

	if ( (state == ScriptState::EDIT) && (CheckHitKey( KEY_INPUT_RETURN ) == 1) )
	{
		FunctionEditCommand editCommand;
		editCommand.insert( std::make_pair( ECOMMAND_ADD,&ModeMainGame::OnEditCommandAdd ) );
		editCommand.insert( std::make_pair( ECOMMAND_DELETE,&ModeMainGame::OnEditCommandDelete ) );
		editCommand.insert( std::make_pair( ECOMMAND_CLEAR,&ModeMainGame::OnEditCommandClear ) );
		editCommand.insert( std::make_pair( ECOMMAND_SAVE,&ModeMainGame::OnEditCommandSave ) );
		editCommand.insert( std::make_pair( ECOMMAND_JUNP,&ModeMainGame::OnEditCommandJunp ) );

		int x = 0; int y = 0;
		std::string buf = "";
		auto cchar = const_cast<char*>(buf.c_str());

		DrawString( x,y,"コマンドを入力してください\nESCで戻る\nadd,ステージ名:オブジェクトの追加\ndelete,ステージ名:オブジェクトの消去\nclear,ステージ名:ステージ名の部分を削除\njump,ステージ名:編集地点変更\nsave:ファイルに書き込み",GetColor( 255,255,255 ) );
		if ( is_notcant )
		{
			is_notcant = false;
			DrawString( x,150,"追加出来るものがありません\n",GetColor( 255,255,255 ) );
		}
		if ( is_notcommand )
		{
			is_notcommand = false;
			DrawString( x,200,"そのようなコマンドはありません\n",GetColor( 255,255,255 ) );
		}
		if ( is_cannotdelete )
		{
			is_cannotdelete = false;
			DrawString( x,250,"消去出来ませんでした\n",GetColor( 255,255,255 ) );
		}

		if ( KeyInputSingleCharString( 0,500,20,cchar,TRUE ) == 1 )
		{
			std::string ecommandbuf = cchar;
			auto editcommand_Stagename = string::Split( ecommandbuf,DELIMITER );

			ClearDrawScreen();
			if ( editcommand_Stagename.empty() )
			{
				is_notcommand = true;
				return;
			}
			if ( editCommand.count( editcommand_Stagename[0] ) <= NONE )
			{
				is_notcommand = true;
				return;
			}

			(this->*editCommand[ecommandbuf])(editcommand_Stagename[1]);
		}
		else
		{
			now_line = 0;
			max_line = scripts_data->GetScriptNum();
			object_main_game.Clear();
			state = ScriptState::PREPARSING;
		};
	}
}

bool ModeMainGame::OnEditCommandAdd( const std::string& command )
{

	int	x = 0,y = 0;

	std::string buf;
	auto cchar = const_cast<char*>(buf.c_str());

	std::vector < std::string >_script;
	const std::string FILEPASS = "res/script/gamescript/gamecommand.json";
	const std::string ARREYNAME = "gamecommand";
	auto adddate = std::make_unique<ScriptsData>();
	adddate->LoadJson( FILEPASS,ARREYNAME );
	auto maxline = adddate->GetScriptNum();

	DrawString( x,y,"何を追加しますか\n追加できるもの",GetColor( 255,255,255 ) );
	y += 38;
	for ( unsigned int line = 0; line < maxline; line++ )
	{
		auto command = string::Split( adddate->GetScriptLine( line ),DELIMITER );

		DrawString( x,y,command[0].c_str(),GetColor( 255,255,255 ) );
		y += 16;
	}


	if ( KeyInputSingleCharString( 0,500,20,cchar,TRUE ) == 1 )
	{
		std::string ecommandbuf = cchar;

		if ( CheckInputString( ecommandbuf,_script ) )
		{
			auto com = string::Combine( _script,DELIMITER );
			scripts_data->ScriptAdd( com );
		}
		else
		{
			ClearDrawScreen();
			is_notcant = true;
		}
	}
	return true;
};

bool ModeMainGame::OnEditCommandDelete( const std::string& command )
{
	int x,y;
	x = y = 0;
	std::string buf = "";
	auto cchar = const_cast<char*>(buf.c_str());
	DrawString( x,y,"何を消去しますか\n番号を入力してください",GetColor( 255,255,255 ) );
	y += 40;
	auto maxline = scripts_data->GetScriptNum();
	for ( unsigned int i = 0; i <= maxline; i++ )
	{
		auto script = scripts_data->GetScriptLine( i );
		auto stringnew = "番号%d" + script;
		DrawFormatString( x,y,GetColor( 255,255,255 ),stringnew.c_str(),i + 1 );
		y += 18;
		if ( i > 54 )
		{
			y = 0;
			x = 400;
		}
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

bool ModeMainGame::OnEditCommandClear( const std::string& command )
{
	scripts_data->ScriptClear();
	return true;
};

bool ModeMainGame::OnEditCommandSave( const std::string& command )
{
	if ( !scripts_data->WriteJson( FILENAME,GAMESCRIPT ) )
	{
		return false;
	};
	return true;
};

bool ModeMainGame::OnEditCommandJunp( const std::string& command )
{
	return true;
};

bool ModeMainGame::CheckInputString( std::string& command,std::vector < std::string >& _sclipt )
{
	FunctionGameCommand comand_funcs;
	comand_funcs.insert( std::make_pair( COMMAND_STAGELABEL,&ModeMainGame::OnCommandStageLabel ) );
	comand_funcs.insert( std::make_pair( COMMAND_JUNPLABEL,&ModeMainGame::OnCommandJumpLabel ) );
	comand_funcs.insert( std::make_pair( COMMAND_TURNING,&ModeMainGame::OnCommandTurning ) );
	comand_funcs.insert( std::make_pair( COMMAND_GAMESTART,&ModeMainGame::OnCommandStart ) );
	comand_funcs.insert( std::make_pair( COMMAND_END,&ModeMainGame::OnCommandEnd ) );
	comand_funcs.insert( std::make_pair( COMMAND_LOADING,&ModeMainGame::OnCommandLoading ) );
	comand_funcs.insert( std::make_pair( COMMAND_FEEDIN,&ModeMainGame::OnCommandCrFeedIn ) );
	comand_funcs.insert( std::make_pair( COMMAND_FEEDOUT,&ModeMainGame::OnCommandCrFeedOut ) );
	comand_funcs.insert( std::make_pair( COMMAND_TIMEWAIT,&ModeMainGame::OnCommandTimeWait ) );
	comand_funcs.insert( std::make_pair( COMMAND_STORY,&ModeMainGame::OnCommandStory ) );


	comand_funcs.insert( std::make_pair( COMMAND_STAGE,&ModeMainGame::OnCommandStage ) );
	comand_funcs.insert( std::make_pair( COMMAND_SKYSPHERE,&ModeMainGame::OnCommandSkySphere ) );
	comand_funcs.insert( std::make_pair( COMMAND_PLAYER,&ModeMainGame::OnCommandPLayer ) );
	comand_funcs.insert( std::make_pair( COMMAND_GUNSHIP,&ModeMainGame::OnCommandGunShip ) );
	comand_funcs.insert( std::make_pair( COMMAND_ENEMYAAA,&ModeMainGame::OnCommandEnemyAAA ) );
	comand_funcs.insert( std::make_pair( COMMAND_AREAAAA,&ModeMainGame::OnCommandAreaAAA ) );
	comand_funcs.insert( std::make_pair( COMMAND_OBJECT,&ModeMainGame::OnCommandObject ) );
	comand_funcs.insert( std::make_pair( COMMAND_AREAOBJECT,&ModeMainGame::OnCommandAreaObj ) );
	comand_funcs.insert( std::make_pair( COMMAND_ENEMYSPAWN,&ModeMainGame::OnCommandAreaSpawn ) );
	comand_funcs.insert( std::make_pair( COMMAND_SUPPLY,&ModeMainGame::OnCommandSupply ) );
	comand_funcs.insert( std::make_pair( COMMAND_AREACOMMUNICATION,&ModeMainGame::OnCommandCommunication ) );
	comand_funcs.insert( std::make_pair( COMMAND_NOENTRY,&ModeMainGame::OnCommandNoEntry ) );

	if ( command.size() <= 0 )
	{
		return false;
	}

	if ( comand_funcs.count( command ) <= 0 )
	{
		return false;
	}
	_sclipt.push_back( command );
	if ( !(this->*comand_funcs[_sclipt[0]])(0,_sclipt) )
	{
		return false;
	}

	state = ScriptState::EDIT;
	object_main_game.Clear();
	return true;
}

bool ModeMainGame::CommandInputString( int posix,int posiy,std::string inputname,std::vector<std::string>& _script )
{
	bool result = false;
	std::string buf = "";
	auto cchar = const_cast<char*>(buf.c_str());
	ClearDrawScreen();
	DrawString( posix,posiy,inputname.c_str(),GetColor( 255,255,255 ) );

	if ( KeyInputSingleCharString( posix + 500,posiy + 500,50,cchar,TRUE ) == 1 )
	{
		std::string ecommandbuf = cchar;

		if ( ecommandbuf.empty() )
		{
			_script.clear();
			return result;
		}
		_script.push_back( ecommandbuf );
		result = true;
	}
	else
	{
		_script.clear();
		return result;
	}
	return result;
}