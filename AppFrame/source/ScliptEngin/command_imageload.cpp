//!
//! @file command_image.cpp
//!
//! @brief 'i' スクリプトを処理するクラス実装
//!
#include "dxlib.h"
#include "command_imageload.h"
#include"../ResourceServer/ResourceServer.h"

namespace
{
	constexpr size_t SCRIPT_NUM = 3;
}

CommandImageload::CommandImageload ( unsigned int line , const std::vector<std::string>& script )
	: CommandBase ( line , script )
{
	handle = -1;
}

bool CommandImageload::Check ()
{
	const auto size = script.size ();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}

	handle = ResourceServer::LoadGraph ( script [ 2 ].c_str () );

	if ( handle == -1 )
	{
		return false;
	}

	return true;
}