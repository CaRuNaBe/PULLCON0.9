#include "CommandMessage.h"

namespace
{
	constexpr size_t SCRIPT_NUM = 3;
}

CommandMessage::CommandMessage( unsigned int line,const std::vector<std::string>& script )
	: CommandBase( line,script )
{
}

bool CommandMessage::Check()
{
	const auto size = script.size();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}

	return true;
}