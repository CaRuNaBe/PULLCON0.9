/*****************************************************************//**
 * \file   command_seload.cpp
 * \brief  'im' スクリプトを処理するクラス実装
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#include <dxlib.h>
#include "CommandSeLoad.h"
#include"../ResourceServer/ResourceServer.h"

namespace
{
	constexpr size_t SCRIPT_NUM = 3;
}

CommandSeLoad::CommandSeLoad( unsigned int line,const std::vector<std::string>& script )
	: CommandBase( line,script )
{
	sehandle = -1;
}

bool CommandSeLoad::Check()
{
	const auto size = script.size();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}

	sehandle = ResourceServer::LoadSoundMem( script[2].c_str() );

	if ( sehandle == -1 )
	{
		return false;
	}

	return true;
}