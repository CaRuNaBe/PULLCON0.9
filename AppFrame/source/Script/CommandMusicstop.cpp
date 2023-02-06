#include "CommandMusicstop.h"
namespace
{
	constexpr size_t SCRIPT_NUM = 2;
}

CommandMusicStop::CommandMusicStop( unsigned int line,const std::vector<std::string>& script )
	: CommandBase( line,script )
{
	mghandle = 0;
}

bool CommandMusicStop::Check()
{
	const auto size = script.size();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}

	return true;
}