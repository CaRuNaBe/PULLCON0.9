/*****************************************************************//**
 * \file   command_musicbag.cpp
 * \brief  'fg' �X�N���v�g����������N���X����
 *
 * \author ���������Y
 * \date   August 2022
 *********************************************************************/
#include "command_musicbag.h"
namespace
{
	constexpr size_t SCRIPT_NUM = 2;
}

CommandMusicbag::CommandMusicbag ( unsigned int line , const std::vector<std::string>& script )
	: CommandBase ( line , script )
{
	mghandle = 0;
}

bool CommandMusicbag::Check ()
{
	const auto size = script.size ();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}


	return true;
}