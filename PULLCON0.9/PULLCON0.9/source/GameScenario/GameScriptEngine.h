/*****************************************************************//**
 * \file   GameScriptEngine.h
 * \brief  ゲームを管理するクラス
 * 
 * \author 阿部健太郎
 * \date   January 2023
 *********************************************************************/
#pragma once


#include <tchar.h>
#include <vector>
#include <string>
#include <memory>
#include "appframe.h"



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
	void Draw( ApplicationBase& _game,ModeBase& mode ) const;



private:
	enum class ScriptState
	{
		EDIT,
		PREPARSING,
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

	void TimeWait();



	bool OnCommandWait( const std::vector<std::string>& scripts );
	bool OnCommandJump( const std::vector<std::string>& scripts );
	bool OnCommandLabel( unsigned int line,const std::vector<std::string>& scripts );

	bool OnCommandChoice( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandDraw( unsigned int line,const std::vector<std::string>& scripts );

	
	std::unique_ptr<ScriptsData> scripts_data;
	ObjectServer<ActorBase3D> _3D_objectServer;
	ScriptState state;

	unsigned int max_line;
	unsigned int now_line;
	unsigned int wait_count;

};

