#pragma once
#include "command_base.h"
#include <string>
class CommandMusicstop :public CommandBase
{
public:
	CommandMusicstop ( unsigned int line , const std::vector<std::string>& script );
	CommandMusicstop ( const CommandMusicstop& ) = default;
	CommandMusicstop ( CommandMusicstop&& ) noexcept = default;

	virtual ~CommandMusicstop () = default;

	CommandMusicstop& operator=( const CommandMusicstop& right ) = default;
	CommandMusicstop& operator=( CommandMusicstop&& right ) noexcept = default;

	bool Check () override;

	inline std::string GetLabel () const
	{
		return script [ 1 ];
	}

	inline int GetMgHandle () const
	{
		return mghandle;
	}
	inline void SetMgHandle ( const int handle )
	{
		this->mghandle = handle;
	}

private:
	int mghandle;
};

