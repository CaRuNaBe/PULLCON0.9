/*****************************************************************//**
 * \file   command_movieplay.cpp
 * \brief   've' �X�N���v�g����������N���X����
 *
 * \author ���������Y
 * \date   August 2022
 *********************************************************************/
#include "CommandMoviePlay.h"
namespace
{
	constexpr size_t SCRIPT_NUM = 2;
}

CommandMoviePlay::CommandMoviePlay( unsigned int line , const std::vector<std::string>& script )
	: CommandBase ( line , script )
{
	mvhandle = 0;
}

bool CommandMoviePlay::Check ()
{
	const auto size = script.size ();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}


	return true;
}