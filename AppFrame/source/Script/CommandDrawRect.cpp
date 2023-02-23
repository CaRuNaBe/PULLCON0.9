#include "CommandDrawRect.h"
#include "ScriptsString.h"
#include "dxlib.h"
namespace
{
	constexpr size_t SCRIPT_NUM = 8;
}

CommandDrawRect::CommandDrawRect( unsigned int line,const std::vector<std::string>& script )
	: CommandBase( line,script )
{
	color = 0;
	posi_x1 = 0;
	posi_y1 = 0;
	posi_x2 = 0;
	posi_y2 = 0;
}

bool CommandDrawRect::Check()
{
	const auto size = script.size();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}

	if ( !string::ToInt( script[1],posi_x1 ) )
	{
		return false;
	}
	if ( !string::ToInt( script[2],posi_y1 ) )
	{
		return false;
	}
	if ( !string::ToInt( script[3],posi_x2 ) )
	{
		return false;
	}
	if ( !string::ToInt( script[4],posi_y2 ) )
	{
		return false;
	}
	int r = 0,g = 0,b = 0;
	if ( !string::ToInt( script[5],r ) )
	{
		return false;
	}
	if ( !string::ToInt( script[6],g ) )
	{
		return false;
	}
	if ( !string::ToInt( script[7],b ) )
	{
		return false;
	}
	color = GetColor( r,g,b );
	return true;
}