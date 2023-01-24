#include "command_musicstop.h"
namespace
{
	constexpr size_t SCRIPT_NUM = 2;
}

CommandMusicstop::CommandMusicstop ( unsigned int line , const std::vector<std::string>& script )
	: CommandBase ( line , script )
{
	mghandle = 0;
}

bool CommandMusicstop::Check ()
{
	const auto size = script.size ();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}

	return true;
}