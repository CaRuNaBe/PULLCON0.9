/*****************************************************************//**
 * \file   command_crfo.cpp
 * \brief  'fi' スクリプトを処理するクラス実装
 *
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#include "command_crfi.h"
#include "scripts_string.h"

namespace
{
	constexpr size_t SCRIPT_NUM = 5;
}

CommandCrfi::CommandCrfi ( unsigned int line , const std::vector<std::string>& script )
	: CommandBase ( line , script )
{
	in_count = 0;
	in_red = 0;
	in_green = 0;
	in_blue = 0;
}

bool CommandCrfi::Check ()
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

	in_count = value;

	if ( !string::ToInt ( script [ 2 ] , value ) )
	{
		return false;
	}

	in_red = value;

	if ( !string::ToInt ( script [ 3 ] , value ) )
	{
		return false;
	}

	in_green = value;

	if ( !string::ToInt ( script [ 4 ] , value ) )
	{
		return false;
	}

	in_blue = value;
	return true;
}