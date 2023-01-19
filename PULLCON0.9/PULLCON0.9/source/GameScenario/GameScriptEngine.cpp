#include "GameScriptEngine.h"


#include <algorithm>

namespace
{
// スクリプト コマンド
	const std::string COMMAND_STAGELABEL = "StageLabel";
	const std::string COMMAND_JUNPLABEL = "StageJunp";
	const std::string COMMAND_GAMESTART = "Start";
	const std::string COMMAND_LOADING = "Load";
	const std::string COMMAND_FEEDIN = "FeedIn";
	const std::string COMMAND_FEEDOUT = "FeedOut";
	const std::string COMMAND_WAIT = "Wait";
	const std::string COMMAND_CLICK = "Click";

	const std::string COMMAND_ADDSTAGE = "AddStage";
	const std::string COMMAND_ADDSKYSPHERE = "AddSkySphere";
	const std::string COMMAND_ADDNORMALOBJECT = "AddObject";
	const std::string COMMAND_ADDCLEAROBJECT = "AddclearObject";
	const std::string COMMAND_ADDENEMYAAAAREA = "AddAnemyaaaArea";
	const std::string COMMAND_ADDENEMYSPAWNERIA = "AddEnemySpawnEria";
	const std::string COMMAND_ADDSUPPLYERIA = "AddSupplyEria";
	const std::string COMMAND_ADDCOMMUNICATIONARIA = "AddCommunicationAria";
	const std::string COMMAND_ADDNOENTRYERIA = "AddNoEntryEria";
	const std::string COMMAND_ADDENEMYAAA = "AddEnemyAAA";


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
		case ScriptState::PARSING:
			Parsing();
			break;



		case ScriptState::END:
			break;
	}


}

//!
//! @fn void ScriptEngine::PreParsing()
//! @brief スクリプトの事前解析
//! @details 'l' コマンド(ラベル)と 'i' コマンド(イメージ)を
//! 予め全て処理してリスト化します。
//!
void GameScriptEngine::PreParsing()
{
	while ( now_line >= 0 && now_line < max_line )
	{
		const auto script = scripts_data->GetScript( now_line );
		const auto command = (script[0])[0];

		switch ( command )
		{
			case COMMAND_L:
				OnCommandLabel( now_line,script );
				break;


			default:
				break;
		}

		++now_line;
	}

	now_line = 0;
}

//!
//! @fn void ScriptEngine::Parsing()
//! @brief スクリプトの解析
//! @details スクリプトを 1 行単位で処理します。
//! (インタープリタ方式)
//!
void GameScriptEngine::Parsing()
{
	auto stop_parsing = false;

	while ( !stop_parsing && (now_line >= 0) && (now_line < max_line) )
	{
		const auto script = scripts_data->GetScript( now_line );
		const auto command = (script[0])[0];

		switch ( command )
		{

			default:
				break;
		}

		++now_line;
	}
}


//!
//! @fn bool ScriptEngine::OnCommandWait(const std::vector<std::string>& scripts)
//! @brief スクリプトの 'w' コマンドを処理
//! @param[in] scripts スクリプトの内容
//! @return 処理の成否
//!
bool GameScriptEngine::OnCommandWait( const std::vector<std::string>& scripts )
{
	auto wait = 0;
	auto result = false;

	return result;
}

//!
//! @fn bool ScriptEngine::OnCommandJump(const std::vector<std::string>& scripts)
//! @brief スクリプトの 'j' コマンドを処理
//! @param[in] scripts スクリプトの内容
//! @return 処理の成否
//!
bool GameScriptEngine::OnCommandJump( const std::vector<std::string>& scripts )
{
	auto line = 0U;
	const auto result = GetLineNumber( scripts[1],line );

	if ( result )
	{
		now_line = line;
	}

	return result;
}

//!
//! @fn bool ScriptEngine::OnCommandLabel(unsigned int line, const std::vector<std::string>& scripts)
//! @brief スクリプトの 'l' コマンドを処理
//! @param[in] line スクリプトの行数
//! @param[in] scripts スクリプトの内容
//! @return 処理の成否
//!
bool GameScriptEngine::OnCommandLabel( unsigned int line,const std::vector<std::string>& scripts )
{

	return true;
}


//!
//! @fn bool ScriptEngine::OnCommandChoice(unsigned int line, const std::vector<std::string>& scripts)
//! @brief スクリプトの 'c' コマンドを処理
//! @param[in] line スクリプトの行数
//! @param[in] scripts スクリプトの内容
//! @return 処理の成否
//!
bool GameScriptEngine::OnCommandChoice( unsigned int line,const std::vector<std::string>& scripts )
{

	return true;
}

//!
//! @fn bool ScriptEngine::OnCommandDraw(unsigned int line, const std::vector<std::string>& scripts)
//! @brief スクリプトの 'd' コマンドを処理
//! @param[in] line スクリプトの行数
//! @param[in] scripts スクリプトの内容
//! @return 処理の成否
//!
bool GameScriptEngine::OnCommandDraw( unsigned int line,const std::vector<std::string>& scripts )
{

	return true;
}


//!
//! @fn void ScriptEngine::TimeWait()
//! @brief 時間待ち処理
//!
void GameScriptEngine::TimeWait()
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



//!
//! @fn void ScriptEngine::Render() const
//! @brief スクリプトの全ての描画処理
//! @details 毎フレーム呼び出す必要があります。
//!
void GameScriptEngine::Draw( ApplicationBase& _game,ModeBase& mode ) const
{}



