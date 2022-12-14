/*****************************************************************//**
 * \file   command_seload.cpp
 * \brief  'im' �X�N���v�g����������N���X����
 *
 * \author ���������Y
 * \date   August 2022
 *********************************************************************/
#include <dxlib.h>
#include "command_seload.h"
#include"../ResourceServer/ResourceServer.h"

namespace
{
	constexpr size_t SCRIPT_NUM = 3;
}

CommandSeload::CommandSeload ( unsigned int line , const std::vector<std::string>& script )
	: CommandBase ( line , script )
{
	sehandle = -1;
}

bool CommandSeload::Check ()
{
	const auto size = script.size ();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}

	sehandle = ResourceServer::LoadSoundMem ( script [ 2 ].c_str () );

	if ( sehandle == -1 )
	{
		return false;
	}

	return true;
}