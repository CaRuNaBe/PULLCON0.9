#include "CommandDrawTime.h"
#include "ScriptsString.h"
namespace
{
	constexpr size_t SCRIPT_NUM = 3;
}

CommandDrawTime::CommandDrawTime( unsigned int line,const std::vector<std::string>& script )
	: CommandBase( line,script )
{
	posi_x = 0;
	posi_y = 0;
}

bool CommandDrawTime::Check()
{
	const auto size = script.size();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}

	if ( !string::ToInt( script[1],posi_x ) )
	{
		return false;
	}
	if ( !string::ToInt( script[2],posi_y ) )
	{
		return false;
	}

	return true;
}