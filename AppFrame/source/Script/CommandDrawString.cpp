#include "CommandDrawString.h"
#include "ScriptsString.h"
#include "dxlib.h"
namespace
{
	constexpr size_t SCRIPT_NUM = 9;
}

CommandDrawString::CommandDrawString( unsigned int line,const std::vector<std::string>& script )
	: CommandBase( line,script )
{
	posi_x = 0;
	posi_y = 0;
	string_handle = -1;
	string_color = 0;
}

bool CommandDrawString::Check()
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
	int string_thick = 0;
	if ( !string::ToInt( script[3],string_thick ) )
	{
		return false;
	}
	int string_size = 0;
	if ( !string::ToInt( script[4],string_size ) )
	{
		return false;
	}
	string_handle = CreateFontToHandle( NULL,string_size,string_thick,-1 );
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
	string_color = GetColor( r,g,b );
	return true;
}