/*****************************************************************//**
 * @file   ModeMainGame.h
 * @brief  ゲームスクリプト定義
 *
 * @author 阿部健太郎
 * @date   January 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
#include <vector>
#include <memory>
#include <string>
#include <array>

class ApplicationMain;
class CommandLabel;
class CommandChoice;
class ModeMainGame:public ModeBase
{
public:
	/** コンストラクタ */
	ModeMainGame( ApplicationMain& game,int layer );
	/** デストラクタ */
	virtual ~ModeMainGame();
	/** 初期化 コンストラクタ時よぶ */
	void Initialize( std::string jsonpath,std::string scriptsname,std::string jsonname );
	/** 計算 毎フレーム呼ばれる */
	virtual bool Update();
	/** 描画 毎フレーム呼ばれる */
	virtual bool Draw();
	/** 後処理 デストラクタ時呼ぶ */
	void Destroy();

	void SetCursor( const vector4& pos )
	{
		_vCursor = pos;
	}

	vector4 _vCursor;
	bool _transparence;
	bool _clear;

	// 開発用
	bool	_dbgCollisionDraw;		// コリジョン表示/非表示
private:
	enum class ScriptState
	{
		EDIT,//エディットモード
		PREPARSING,//プレパース
		PARSING,
		GAME,
		STORY,
		RESULT,
		CRFEEDIN,
		CRFEEDOUT,
		TIME_WAIT,
		CLICK_WAIT,
		LOADING,
		END,
	};


	void PreParsing();
	void Parsing();

	bool OnCommandStageLabel( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandJumpLabel( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandTurning( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandStart( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandEnd( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandLoading( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandCrFeedIn( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandCrFeedOut( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandTimeWait( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandBgm( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandStory( unsigned int line,std::vector<std::string>& scripts );



	bool OnCommandStage( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandSkySphere( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandPLayer( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandGunShip( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandEnemyAAA( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandAreaAAA( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandObject( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandAreaObj( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandAreaSpawn( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandSupply( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandCommunication( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandNoEntry( unsigned int line,std::vector<std::string>& scripts );




	/** エディットモードの時に入る関数 */
	void Edit();
	/** 入力されたコマンドがゲームで使われるか確認 */
	bool CheckInputString( std::string& command,std::vector < std::string >& _sclipt );
	/** 汎用入力関数 */
	bool CommandInputString( int posix,int posiy,std::string inputname,std::vector<std::string>& _script );
	/** 追加コマンドに使われる関数 */
	bool OnEditCommandAdd( const std::string& command );
	/** 消去コマンドに使われる関数 */
	bool OnEditCommandDelete( const std::string& command );
	/** 初期化コマンドに使われる関数 */
	bool OnEditCommandClear( const std::string& command );
	/** 保存コマンドに使われる関数 */
	bool OnEditCommandSave( const std::string& command );
	/** 編集地点変更コマンドに使われる関数 */
	bool OnEditCommandJunp( const std::string& command );



	/** フレーム数待つ時に使われるUpdate */
	void TimeWait();
	/** 文字列に対応した行数を取得 */
	bool GetLineNumber( const std::string& str,unsigned int& line ) const;
	/** フェードイン時に使われるUpdate */
	void CrfiUpdate();
	/** フェードアウト時に使われるUpdate */
	void CrfoUpdate();
	/** フェードイン描画 */
	void DrawFeedIn()const;
	/** フェードアウト描画 */
	void DrawFeedOut()const;

	/** ScriptsDataにアクセスするポインタ */
	std::unique_ptr<ScriptsData> scripts_data;
	/** ステージ名を格納するvector */
	std::vector<std::unique_ptr<CommandLabel>> label_list;
	std::vector < std::unique_ptr < CommandCrFeedIn>> crfi_list;
	std::vector < std::unique_ptr < CommandCrFeedOut>> crfo_list;


	/** ゲームのステータス */
	ScriptState state;
	/** ゲームコマンドに使われる文字列をキーとした関数ポインタ */
	using FunctionGameCommand = std::map<std::string,bool(ModeMainGame::*)(unsigned int,std::vector<std::string>&)>;
	/** エディットコマンドの時に使われる文字列をキーとした関数ポインタ */
	using FunctionEditCommand = std::map<std::string,bool(ModeMainGame::*)(const std::string&)>;
	/** スクリプトの最大行数 */
	unsigned int max_line;
	/** 今の行数 */
	unsigned int now_line;
	/** 待つ時間 */
	unsigned int wait_count;
	/** フェードアウトインするときに使うα値 */
	float alpha;
	/** フェードアウトインするときに使うフレーム数 */
	float feedcount;
	/** ステージ名 */
	std::string  stage_name;
	/** ゲームスタート時間 */
	int start_time;

	bool is_notcant;
	bool is_notcommand;
	bool is_cannotdelete;

	int _cg;
	int _handlefont;
};
