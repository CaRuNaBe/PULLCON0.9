/*****************************************************************//**
 * \file   command_drawin.cpp
 * \brief  'di' スクリプトを処理するクラス実装
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/

#include "CommandDrawIn.h"
#include "ScriptsString.h"
namespace
{
	constexpr size_t SCRIPT_NUM = 6;
}

CommandDrawIn::CommandDrawIn( unsigned int line , const std::vector<std::string>& script )
	: CommandBase ( line , script )
{
	index = 0;
	x = 0;
	y = 0;
	in_count = 0;
	handle = 0;
	_DrawAlphain = 255.0;
	isdrawincomplete = true;
}

bool CommandDrawIn::Check ()
{
	const auto size = script.size ();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}

	auto value = 0;

	if ( !string::ToInt ( script [ 1 ] , value ) )
	{
		return false;
	}

	index = value;

	if ( !string::ToInt ( script [ 2 ] , value ) )
	{
		return false;
	}

	x = value;

	if ( !string::ToInt ( script [ 3 ] , value ) )
	{
		return false;
	}

	y = value;

	if ( !string::ToInt ( script [ 4 ] , value ) )
	{
		return false;
	}

	in_count = value;

	if ( in_count == 0 )
	{
		_DrawAlphain = 255;
		isdrawincomplete = true;
	}
	else
	{
		_DrawAlphain = 0;
		isdrawincomplete = false;
	}
	return true;
}