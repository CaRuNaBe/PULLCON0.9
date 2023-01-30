//!
//! @file command_choice.h
//!
//! @brief 'c' スクリプトを処理するクラス定義
//!
#pragma once

#include "CommandBase.h"
#include <string>


class CommandChoice final: public CommandBase
{
public:
	CommandChoice( unsigned int line,const std::vector<std::string>& script );
	CommandChoice( const CommandChoice& ) = default;
	CommandChoice( CommandChoice&& ) noexcept = default;

	virtual ~CommandChoice() = default;

	CommandChoice& operator=( const CommandChoice& right ) = default;
	CommandChoice& operator=( CommandChoice&& right ) noexcept = default;

	bool Check() override;

	inline void Initialize( const int line )
	{
	 this->line = line;
	}

	inline std::string GetLabel() const
	{
		return script[1];
	}
	inline std::string GetMessage() const
	{
		return script[2];
	}

	inline unsigned int GetLineNumber() const
	{
		return line;
	}





private:
	unsigned int line;
};

