﻿//!
//! @file script_engine.h
//!
//! @brief スクリプトエンジンの定義
//!
#pragma once

#include "rect.h"
#include "../appframe.h"
#include <tchar.h>
#include <vector>
#include <string>
#include <memory>
#include <map>


class ScriptsData;

class CommandImageload;
class CommandSeload;
class CommandCrfi;
class CommandCrfo;
class CommandMovieplay;
class CommandMessage;
class CommandDrawin;
class CommandDrawout;
class CommandMusicloop;
class CommandMusicbag;
class ApplicationBase;
class ModeBase;


class ScriptEngine
{
public:
	ScriptEngine ( std::string storyname);
	ScriptEngine ( const ScriptEngine& ) = default;
	ScriptEngine ( ScriptEngine&& ) noexcept = default;

	virtual ~ScriptEngine ();

	ScriptEngine& operator=( const ScriptEngine& right ) = default;
	ScriptEngine& operator=( ScriptEngine&& right ) noexcept = default;

	void Destroy ();

	void Update (ApplicationBase& game);
	void Draw (ApplicationBase& game) const;

private:
	enum class ScriptState
	{
		PREPARSING ,
		PARSING ,
		CRFEEDIN ,
		CRFEEDOUT ,
		PLAY_ANIME ,
		TIME_WAIT ,
		CLICK_WAIT ,
		SCRIPT_END
	};

	bool InitializeStrings ();

	void PreParsing ();
	void Parsing ();
	void UpdateMessage ();
	void Hide_Message ();
	void feed_draw ();
	void Speak_skip ();
	void Script_skip ();
	bool CalculateMessageArea ( const std::string& message , Rect& area , int& right_goal );


	void PlayUpdate ();;
	void TimeWait ();
	void ClickWait ();
	void CrfiUpdate ();
	void CrfoUpdate ();

	bool GetImageHandle ( const std::string& str , int& handle ) const;
	bool GetSeHandle ( const std::string& str , int& handle ) const;

	bool OnCommandClick ( unsigned int line , const std::vector<std::string>& scripts );
	bool OnCommandWait ( unsigned int line , const std::vector<std::string>& scripts );
	bool OnCommandCrfi ( unsigned int line , const std::vector<std::string>& scripts );
	bool OnCommandCrfo ( unsigned int line , const std::vector<std::string>& scripts );
	bool OnCommandDrawin ( unsigned int line , const std::vector<std::string>& scripts );
	bool OnCommandDrawout ( unsigned int line , const std::vector<std::string>& scripts );
	bool OnCommandMessage ( unsigned int line , const std::vector<std::string>& scripts );
	bool OnCommandMusicloop ( unsigned int line , const std::vector<std::string>& scripts );
	bool OnCommandMusicbag ( unsigned int line , const std::vector<std::string>& scripts );
	bool OnCommandMusicstop ( unsigned int line , const std::vector<std::string>& scripts );
	bool OnCommandPlayanime ( unsigned int line , const std::vector<std::string>& scripts );
	bool OnCommandScliptend ( unsigned int line , const std::vector<std::string>& scripts );

	bool OnCommandImage ( unsigned int line , const std::vector<std::string>& scripts );
	bool OnCommandSe ( unsigned int line , const std::vector<std::string>& scripts );





	void DrawImage () const;
	void DrawMessageWindow () const;
	void DrawMessage () const;
	void DrawFeedin ()const;
	void DrawFeedout ()const;
	void DrawAnime ()const;

	std::unique_ptr<ScriptsData> scripts_data;
	std::unique_ptr<CommandMovieplay>movie_play;

	std::vector<std::unique_ptr<CommandImageload>> image_list;
	std::vector<std::unique_ptr<CommandSeload>> se_list;
	std::vector < std::unique_ptr < CommandCrfi>> crfi_list;
	std::vector < std::unique_ptr < CommandCrfo>> crfo_list;
	std::vector<std::unique_ptr<CommandDrawin>> drawin_list;
	std::vector<std::unique_ptr<CommandDrawout>> drawout_list;
	std::vector<std::unique_ptr<CommandMessage>> message_list;


	typedef std::map<std::string , bool( ScriptEngine::* )( unsigned int , const std::vector<std::string>& scripts )> funcs_type;

	ScriptState state;


	unsigned int max_line;//
	unsigned int now_line;
	unsigned int wait_count;
	double _Alpha;
	double feedcount;
	int Speak_skip_count;
	int Script_skip_count;
	int Anime_count;
	int Hide_point;

	bool is_finishdraw;
	bool is_click_wait_visible;
	bool is_message_output;
	bool is_Skip_ok;
	bool 	is_Click_on;
	bool is_hide;
	bool is_amime_skip;
};
