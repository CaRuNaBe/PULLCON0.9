#pragma once
#include "appframe.h"
#include<vector>
#include<memory>
#include<string>

class ApplicationMain;
class CommandCrfi;
class CommandCrfo;

class ModeMainGame:public ModeBase
{
public:
	ModeMainGame( ApplicationMain& game,int layer );
	virtual ~ModeMainGame();

	void Initialize( std::string jsonpath,std::string scriptsname,std::string jsonname );



	virtual bool Draw();	// 描画

	void Destroy();

	void SetCursor(const vector4& pos) { _vCursor = pos; }

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

	bool OnCommandStageLabel( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandJunpLabel( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandChoice( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandStart( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandEnd( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandLoading( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandFeedIn( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandFeedOut( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandTimeWait( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandClick( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandBgm( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandStory( unsigned int line,const std::vector<std::string>& scripts );



	bool OnCommandStage( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandSkySphere( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandPLayer( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandGunShip( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandEnemyAAA( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandAreaAAA( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandObject( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandAreaObj( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandAreaSpawn( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandSupply( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandCommunication( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandNoEntry( unsigned int line,const std::vector<std::string>& scripts );




	/** エディットモードの時に入る関数 */
	void Edit();
	/** 入力されたコマンドがゲームで使われるか確認 */
	bool CheckInputString( std::string command );
	/** 追加コマンドに使われる関数 */
	bool OnEditCommandAdd();
	/** 消去コマンドに使われる関数 */
	bool OnEditCommandDelete();
	/** 初期化コマンドに使われる関数 */
	bool OnEditCommandClear();
	/** 保存コマンドに使われる関数 */
	bool OnEditCommandSave();
	/** 編集地点変更コマンドに使われる関数 */
	bool OnEditCommandJunp();
	/** 毎フレーム呼ばれる */
	virtual bool Update();
	/** フレーム数待つ時に使われるUpdate */
	void TimeWait();
	/** ボタン押すまで待つに使われるUpdate */
	void ClickWait();
	/** フェードイン時に使われるUpdate */
	void CrfiUpdate();
	/** フェードアウト時に使われるUpdate */
	void CrfoUpdate();

	//void DrawFeedin( ApplicationBase& game )const;
	//void DrawFeedout( ApplicationBase& game )const;

	/** ScriptsDataにアクセスするポインタ */
	std::unique_ptr<ScriptsData> scripts_data;

	//std::vector<std::unique_ptr<CommandCrfi>> crfi_list;
	//std::vector<std::unique_ptr<CommandCrfo>> crfo_list;

	/** ゲームのステータス */
	ScriptState state;
	/** ゲームコマンドに使われる文字列をキーとした関数ポインタ */
	using FunctionGameCommand = std::map<std::string,bool(ModeMainGame::*)(unsigned int,const std::vector<std::string>& scripts)>;
	/** エディットコマンドの時に使われる文字列をキーとした関数ポインタ */
	using FunctionEditCommand = std::map<std::string,bool(ModeMainGame::*)()>;
	/** スクリプトの最大行数 */
	unsigned int max_line;
	/** 今の行数 */
	unsigned int now_line;
	/** 待つ時間 */
	unsigned int wait_count;
	/** フェードアウトインするときに使うα値 */
	double Alpha;
	/** フェードアウトインするときに使うフレーム数 */
	double feedcount;
	/** ステージ名 */
	std::string  stage_name;
	bool is_notcant;
	bool is_notcommand;
	bool is_cannotdelete;

	int _cg;
	int _handlefont;
};
