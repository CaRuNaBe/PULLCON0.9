/*****************************************************************//**
 * \file   command_drawout.cpp
 * \brief   'do' スクリプトを処理するクラス実装
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#include "CommandDrawOut.h"
#include "ScriptsString.h"
namespace
{
	constexpr size_t SCRIPT_NUM = 6;
}

CommandDrawOut::CommandDrawOut( unsigned int line , const std::vector<std::string>& script )
	: CommandBase ( line , script )
{
	index = 0;
	x = 0;
	y = 0;
	out_count = 0;
	handle = 0;
	_DrawAlphaout = 0.0;
	isdrawoutcomplete = true;
}

bool CommandDrawOut::Check ()
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

	out_count = value;

	if ( out_count == 0 )
	{
		_DrawAlphaout = 0;
		isdrawoutcomplete = true;
	}
	else
	{
		_DrawAlphaout = 255;
		isdrawoutcomplete = false;
	}
	return true;
}