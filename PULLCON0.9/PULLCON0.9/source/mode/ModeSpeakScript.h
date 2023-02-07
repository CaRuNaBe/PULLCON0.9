#pragma once
#include "appframe.h"
#include <tchar.h>
#include <vector>
#include <string>
#include <memory>
#include <map>


class ScriptsData;



class ModeSpeakScript:public ModeBase
{

public:
	ModeSpeakScript( ApplicationBase& game,int layer,std::string storyname );
	ModeSpeakScript( const ModeSpeakScript& ) = default;
	ModeSpeakScript( ModeSpeakScript&& ) noexcept = default;

	virtual ~ModeSpeakScript();

	ModeSpeakScript& operator=( const ModeSpeakScript& right ) = default;
	ModeSpeakScript& operator=( ModeSpeakScript&& right ) noexcept = default;

	/** 初期化 コンストラクタ時よぶ */
	virtual void Initialize( std::string jsonpath,std::string scriptsname,std::string jsonname );
	/** 計算 毎フレーム呼ばれる */
	virtual bool Update();
	/** 描画 毎フレーム呼ばれる */
	virtual bool Draw();
	/** 後処理 デストラクタ時呼ぶ */
	void Destroy();
private:
	enum class ScriptState
	{
		PREPARSING,
		PARSING,
		CRFEEDIN,
		CRFEEDOUT,
		PLAY_ANIME,
		TIME_WAIT,
		CLICK_WAIT,
		SCRIPT_END
	};


	void PreParsing();
	void Parsing();
	void FeedDraw();


	void PlayUpdate();;
	void TimeWait();
	void ClickWait();
	void CrfiUpdate();
	void CrfoUpdate();

	bool GetImageHandle( const std::string& str,int& handle ) const;
	bool GetSeHandle( const std::string& str,int& handle ) const;

	bool OnCommandClick( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandWait( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandCrfi( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandCrfo( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandDrawIn( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandDrawOut( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandMessage( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandMusicloop( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandMusicbag( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandMusicstop( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandPlayanime( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandScriptend( unsigned int line,const std::vector<std::string>& scripts );

	bool OnCommandImage( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandSe( unsigned int line,const std::vector<std::string>& scripts );

	void DrawImage() const;
	void DrawMessage() const;
	void DrawFeedIn()const;
	void DrawFeedOut()const;
	void DrawAnime()const;

	std::unique_ptr<ScriptsData> scripts_data;
	std::unique_ptr<CommandMoviePlay>movie_play;

	std::vector<std::unique_ptr<CommandImageLoad>> image_list;
	std::vector<std::unique_ptr<CommandSeLoad>> se_list;
	std::vector < std::unique_ptr < CommandCrFeedIn>> crfi_list;
	std::vector < std::unique_ptr < CommandCrFeedOut>> crfo_list;
	std::vector<std::unique_ptr<CommandDrawIn>> drawin_list;
	std::vector<std::unique_ptr<CommandDrawOut>> drawout_list;
	std::vector<std::unique_ptr<CommandMessage>> message_list;


	typedef std::map<std::string,bool(ModeSpeakScript::*)(unsigned int,const std::vector<std::string>& scripts)> funcs_type;

	ScriptState state;

	unsigned int max_line;
	unsigned int now_line;

	unsigned int wait_count;

	float alpha;
	float feed_count;
	int anime_count;

	bool is_finishdraw;

};
