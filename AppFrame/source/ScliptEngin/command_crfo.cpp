/*****************************************************************//**
 * \file   command_crfo.cpp
 * \brief  'fo' スクリプトを処理するクラス実装
 *
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#include "command_crfo.h"
#include "scripts_string.h"

namespace
{
	constexpr size_t SCRIPT_NUM = 5;
}

CommandCrfo::CommandCrfo ( unsigned int line , const std::vector<std::string>& script )
	: CommandBase ( line , script )
{
	out_count = 0;
	out_red = 0;
	out_green = 0;
	out_blue = 0;
}

bool CommandCrfo::Check ()
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

	out_count = value;

	if ( !string::ToInt ( script [ 2 ] , value ) )
	{
		return false;
	}

	out_red = value;

	if ( !string::ToInt ( script [ 3 ] , value ) )
	{
		return false;
	}

	out_green = value;

	if ( !string::ToInt ( script [ 4 ] , value ) )
	{
		return false;
	}

	out_blue = value;
	return true;
}
