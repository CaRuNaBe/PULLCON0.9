/*****************************************************************//**
 * \file   command_movieplay.cpp
 * \brief   've' スクリプトを処理するクラス実装
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#include "command_movieplay.h"
namespace
{
	constexpr size_t SCRIPT_NUM = 2;
}

CommandMovieplay::CommandMovieplay ( unsigned int line , const std::vector<std::string>& script )
	: CommandBase ( line , script )
{
	mvhandle = 0;
}

bool CommandMovieplay::Check ()
{
	const auto size = script.size ();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}


	return true;
}