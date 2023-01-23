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

	virtual bool Update(); // 更新

	virtual bool Draw();	// 描画

	void Destroy();


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
	void Edit();

	bool OnCommandAddPLayer( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandAddStage( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandAddSkySphere( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandAddClearObject( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandAddAreaSupply( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandAddEnemyAAA( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandAddAreaEnemyAAA( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandStart( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandCrfi( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandCrfo( unsigned int line,const std::vector<std::string>& scripts );

	void TimeWait();
	void ClickWait();
	void CrfiUpdate();
	void CrfoUpdate();
	bool CheckInputString( std::string command );
	void DrawFeedin( ApplicationBase& game )const;
	void DrawFeedout( ApplicationBase& game )const;

	std::shared_ptr<ScriptsData> scripts_data;
	std::vector<std::unique_ptr<CommandCrfi>> crfi_list;
	std::vector<std::unique_ptr<CommandCrfo>> crfo_list;
	ScriptState state;
	using FuncsType = std::map<std::string,bool(ModeMainGame::*)(unsigned int,const std::vector<std::string>& scripts)>;
	unsigned int max_line;
	unsigned int now_line;
	unsigned int wait_count;
	double _Alpha;
	double feedcount;

	bool is_notcant;

};
