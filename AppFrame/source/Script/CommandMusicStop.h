#pragma once
#include "CommandBase.h"
#include <string>
class CommandMusicStop :public CommandBase
{
public:
	CommandMusicStop( unsigned int line , const std::vector<std::string>& script );
	CommandMusicStop( const CommandMusicStop& ) = default;
	CommandMusicStop( CommandMusicStop&& ) noexcept = default;

	virtual ~CommandMusicStop() = default;

	CommandMusicStop& operator=( const CommandMusicStop& right ) = default;
	CommandMusicStop& operator=( CommandMusicStop&& right ) noexcept = default;

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

