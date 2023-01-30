
#include "CommandChoice.h"

namespace
{
	constexpr size_t SCRIPT_NUM = 3;
}


CommandChoice::CommandChoice( unsigned int line,const std::vector<std::string>& script )
	: CommandBase( line,script )
{
	this->line = 0;
}

bool CommandChoice::Check()
{
	const auto size = script.size();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}

	return true;
}
