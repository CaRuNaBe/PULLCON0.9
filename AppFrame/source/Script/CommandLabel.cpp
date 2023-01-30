
#include "CommandLabel.h"

namespace
{
	constexpr size_t SCRIPT_NUM = 2;
}


CommandLabel::CommandLabel( unsigned int line,const std::vector<std::string>& script )
	: CommandBase( line,script )
{
}

bool CommandLabel::Check()
{
	const auto size = script.size();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}

	return true;
}
