/*****************************************************************//**
 * \file   GameScriptEngine.h
 * \brief  ゲームを管理するクラス
 * 
 * \author 阿部健太郎
 * \date   January 2023
 *********************************************************************/
#pragma once


#include <vector>
#include <string>
#include <memory>
#include "appframe.h"


using namespace math;
class GameScriptEngine
{
public:
	GameScriptEngine();
	GameScriptEngine( const GameScriptEngine& ) = default;
	GameScriptEngine( GameScriptEngine&& ) noexcept = default;

	virtual ~GameScriptEngine();

	GameScriptEngine& operator=( const GameScriptEngine& right ) = default;
	GameScriptEngine& operator=( GameScriptEngine&& right ) noexcept = default;

	bool Initialize( std::string jsonpath,std::string scriptsname,std::string jsonname );
	void Destroy();

	void Update( ApplicationBase& _game,ModeBase& mode );
	void Draw( ApplicationBase& _game,ModeBase& mode ) ;

	ObjectServer<ActorBase3D>& GetObjectServer3D()
	{
		return _3D_objectServer;
	}

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
	bool OnCommandAddSupplyEria( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandAddEnemyAAA( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandEreaAddEnemyAAA( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandStart( unsigned int line,const std::vector<std::string>& scripts );

	
	std::shared_ptr<ScriptsData> scripts_data;
	ObjectServer<ActorBase3D> _3D_objectServer;
	ScriptState state;

	unsigned int max_line;
	unsigned int now_line;
	unsigned int wait_count;

};

