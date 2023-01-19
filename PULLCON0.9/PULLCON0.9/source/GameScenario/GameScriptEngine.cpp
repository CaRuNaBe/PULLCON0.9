#include"GameScriptEngine.h"
#include"../maingame/Player.h"
#include"../maingame/GameStage.h"
#include"../maingame/SkySphere.h"
#include"../maingame/SupplyEria.h"
#include"../maingame/ClearObject.h"
#include"../maingame/EnemyAAA.h"
#include<algorithm>

namespace
{
// スクリプト コマンド
	const std::string COMMAND_STAGELABEL = "StageLabel";
	const std::string COMMAND_JUNPLABEL = "StageJunp";
	const std::string COMMAND_CHOICE = "StageChoice";
	const std::string COMMAND_GAMESTART = "Start";//1
	const std::string COMMAND_LOADING = "Load";
	const std::string COMMAND_FEEDIN = "FeedIn";
	const std::string COMMAND_FEEDOUT = "FeedOut";
	const std::string COMMAND_WAIT = "Wait";
	const std::string COMMAND_CLICK = "Click";

	const std::string COMMAND_ADDSTAGE = "AddStage";//1
	const std::string COMMAND_ADDSKYSPHERE = "AddSkySphere";//1
	const std::string COMMAND_ADDNORMALOBJECT = "AddObject";
	const std::string COMMAND_ADDCLEAROBJECT = "AddClearObject";//1
	const std::string COMMAND_ADDENEMYAAAAREA = "AddAnemyaaaArea";//1
	const std::string COMMAND_ADDENEMYSPAWNERIA = "AddEnemySpawnEria";
	const std::string COMMAND_ADDSUPPLYERIA = "AddSupplyEria";
	const std::string COMMAND_ADDCOMMUNICATIONARIA = "AddCommunicationAria";
	const std::string COMMAND_ADDNOENTRYERIA = "AddNoEntryEria";
	const std::string COMMAND_ADDENEMYAAA = "AddEnemyAAA";//1
	const std::string COMMAND_ADDPLAYER = "AddPlayer";
	//編集コマンド
	const std::string ECOMMAND_ADD = "add";
	const std::string ECOMMAND_EDIT = "edit";
	const std::string ECOMMAND_DELETE = "delete";
	const std::string ECOMMAND_START = "start";
}


GameScriptEngine::GameScriptEngine():_3D_objectServer()
{
	scripts_data = nullptr;
	state = ScriptState::PREPARSING;
#if _DEBUG
	state = ScriptState::EDIT;
#endif
	max_line = 0;
	now_line = 0;

}

GameScriptEngine::~GameScriptEngine()
{
	Destroy();
}

//!
//! @fn bool ScriptEngine::Initialize(const TCHAR* path)
//! @brief スクリプトエンジンの初期化
//! @param[in] path パス付のスクリプト用 Json ファイル名
//! @return 処理の成否
//! @details スクリプトの事前の処理と
//! DX ライブラリの設定などを行い
//! スクリプトエンジンが動作する様にします。
//!
bool GameScriptEngine::Initialize( std::string jsonpath,std::string scriptsname,std::string jsonname )
{
	if ( scripts_data != nullptr )
	{
		return false;
	}


	scripts_data.reset( new ScriptsData() );

	if ( !scripts_data->LoadJson( jsonpath,scriptsname,jsonname ) )
	{
		return false;
	}

	max_line = scripts_data->GetScriptNum();

	if ( max_line <= 0 )
	{
		return false;
	}

	PreParsing();


	return true;
}

//!
//! @fn void ScriptEngine::Destroy()
//! @brief 明示的なスクリプトエンジンの終了処理
//! @details 無理に呼び出す必要はありませんが
//! インスタンスを再利用したい場合などに呼び出します。
//!
void GameScriptEngine::Destroy()
{
	scripts_data.reset();
	scripts_data = nullptr;

	state = ScriptState::PARSING;
	max_line = 0;
	now_line = 0;
	wait_count = 0;
}

//!
//! @fn void ScriptEngine::Update()
//! @brief スクリプトエンジンの更新処理
//! @details 毎フレーム呼び出す必要があります。
//!
void GameScriptEngine::Update( ApplicationBase& _game,ModeBase& mode )
{
	switch ( state )
	{
		case ScriptState::EDIT:
			Edit();
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
			break;

		case ScriptState::CRFEEDOUT:
			break;

		case ScriptState::LOADING:
			break;

		case ScriptState::END:
			break;
	}
	_3D_objectServer.Update( _game,mode );
}

//!
//! @fn void ScriptEngine::PreParsing()
//! @brief スクリプトの事前解析
//! @details 'l' コマンド(ラベル)と 'i' コマンド(イメージ)を
//! 予め全て処理してリスト化します。
//!
void GameScriptEngine::PreParsing()
{

}
//!
//! @fn void ScriptEngine::Parsing()
//! @brief スクリプトの解析
//! @details スクリプトを 1 行単位で処理します。
//! (インタープリタ方式)
//!
void GameScriptEngine::Parsing()
{

}

bool GameScriptEngine::OnCommandAddPLayer( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	string::ToFloat( scripts[1],posi.x );
	string::ToFloat( scripts[2],posi.y );
	string::ToFloat( scripts[3],posi.z );
	auto player = std::make_shared<Player>();
	player->SetPosition( posi );
	_3D_objectServer.Add( player );
};
bool GameScriptEngine::OnCommandAddStage( unsigned int line,const std::vector<std::string>& scripts )
{
	auto stage = std::make_shared<GameStage>();
	_3D_objectServer.Add( stage );
};
bool GameScriptEngine::OnCommandAddSkySphere( unsigned int line,const std::vector<std::string>& scripts )
{
	auto skysphere = std::make_shared<SkySphere>();
	_3D_objectServer.Add( skysphere );
};
bool GameScriptEngine::OnCommandAddClearObject( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	string::ToFloat( scripts[1],posi.x );
	string::ToFloat( scripts[2],posi.y );
	string::ToFloat( scripts[3],posi.z );
	auto clearobject = std::make_shared<ClearObject>();
	clearobject->SetPosition( posi );
	_3D_objectServer.Add( clearobject );
};
bool GameScriptEngine::OnCommandAddSupplyEria( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	string::ToFloat( scripts[1],posi.x );
	string::ToFloat( scripts[2],posi.y );
	string::ToFloat( scripts[3],posi.z );
	auto supplyeria = std::make_shared<SupplyEria>();
	supplyeria->SetPosition( posi );
	_3D_objectServer.Add( supplyeria );
};
bool GameScriptEngine::OnCommandAddEnemyAAA( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	string::ToFloat( scripts[1],posi.x );
	string::ToFloat( scripts[2],posi.y );
	string::ToFloat( scripts[3],posi.z );
	auto enemyAAA = std::make_shared<EnemyAAA>();
	enemyAAA->SetPosition( posi );
	_3D_objectServer.Add( enemyAAA );
};

bool GameScriptEngine::OnCommandEreaAddEnemyAAA( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	string::ToFloat( scripts[1],posi.x );
	string::ToFloat( scripts[2],posi.y );
	string::ToFloat( scripts[3],posi.z );
	float range = 0.0f;
	string::ToFloat( scripts[4],range );
	int max = 0;
	string::ToInt( scripts[5],max );
	for ( int i = 0; i < max; i++ )
	{
		vector4 AAAposi = {static_cast<float>(utility::get_random( posi.x,posi.x + range ))
			,static_cast<float>(utility::get_random( posi.y,posi.y + range ))
			,posi.z};

		auto enemyAAA = std::make_shared<EnemyAAA>();
		enemyAAA->SetPosition( AAAposi );
		_3D_objectServer.Add( enemyAAA );
	}

};
bool GameScriptEngine::OnCommandStart( unsigned int line,const std::vector<std::string>& scripts )
{
	state = ScriptState::GAME;
};

void GameScriptEngine::Edit()
{

}

//!
//! @fn void ScriptEngine::Render() const
//! @brief スクリプトの全ての描画処理
//! @details 毎フレーム呼び出す必要があります。
//!
void GameScriptEngine::Draw( ApplicationBase& _game,ModeBase& mode )
{
	switch ( state )
	{
		case ScriptState::EDIT:

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
	_3D_objectServer.Draw( _game,mode );
}



