
#include "CommandMusicBack.h"
namespace
{
	constexpr size_t SCRIPT_NUM = 2;
}

CommandMusicBack::CommandMusicBack( unsigned int line , const std::vector<std::string>& script )
	: CommandBase ( line , script )
{
	mghandle = 0;
}

bool CommandMusicBack::Check ()
{
	const auto size = script.size ();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}


	return true;
}