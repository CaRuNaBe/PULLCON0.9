/*****************************************************************//**
 * \file   command_musicloop.cpp
 * \brief  'bg' スクリプトを処理するクラス実装
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#include "CommandMusicLoop.h"
namespace
{
	constexpr size_t SCRIPT_NUM = 2;
}

CommandMusicLoop::CommandMusicLoop( unsigned int line , const std::vector<std::string>& script )
	: CommandBase ( line , script )
{
	mghandle = 0;
}

bool CommandMusicLoop::Check ()
{
	const auto size = script.size ();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}


	return true;
}