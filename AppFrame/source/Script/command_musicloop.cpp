/*****************************************************************//**
 * \file   command_musicloop.cpp
 * \brief  'bg' �X�N���v�g����������N���X����
 *
 * \author ���������Y
 * \date   August 2022
 *********************************************************************/
#include "command_musicloop.h"
namespace
{
	constexpr size_t SCRIPT_NUM = 2;
}

CommandMusicloop::CommandMusicloop ( unsigned int line , const std::vector<std::string>& script )
	: CommandBase ( line , script )
{
	mghandle = 0;
}

bool CommandMusicloop::Check ()
{
	const auto size = script.size ();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}


	return true;
}