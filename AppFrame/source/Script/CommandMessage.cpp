//!
//! @file command_message.cpp
//!
//! @brief 'm' スクリプトを処理するクラス実装
//!
#include "CommandMessage.h"

namespace
{
	constexpr size_t SCRIPT_NUM = 3;
}

CommandMessage::CommandMessage ( unsigned int line , const std::vector<std::string>& script )
	: CommandBase ( line , script )
{
	right_goal = 0;
}

bool CommandMessage::Check ()
{
	const auto size = script.size ();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}

	return true;
}