#pragma once
#include "appframe.h"
class ModeScriptBase:public ModeBase
{
public:
	ModeScriptBase( ApplicationBase& game,int layer,std::string storyname );
	ModeScriptBase( const ModeScriptBase& ) = default;
	ModeScriptBase( ModeScriptBase&& ) noexcept = default;

	virtual ~ModeScriptBase();

	ModeScriptBase& operator=( const ModeScriptBase& right ) = default;
	ModeScriptBase& operator=( ModeScriptBase&& right ) noexcept = default;

	void Destroy();

	void Update();
	void Draw() const;

private:
	enum class ScriptState
	{
		PRE_PARSING,
		PARSING,
		RUN,
		SCRIPT_END
	};

	void PreParsing();
	void Parsing();
	std::unique_ptr<ScriptsData> scripts_data;




	unsigned int max_line;
	unsigned int now_line
};

