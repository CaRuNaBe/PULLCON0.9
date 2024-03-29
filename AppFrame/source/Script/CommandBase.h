﻿#pragma once

#include <vector>
#include <string>

class CommandBase
{
public:
	CommandBase( unsigned int line,const std::vector<std::string>& script )
	{
		this->line = line; this->script = script;
	}
	CommandBase( const CommandBase& ) = default;
	CommandBase( CommandBase&& ) noexcept = default;

	virtual ~CommandBase() = default;

	CommandBase& operator=( const CommandBase& right ) = default;
	CommandBase& operator=( CommandBase&& right ) noexcept = default;

	virtual bool Check() = 0;

	inline unsigned int GetLineNumber() const
	{
		return line;
	}
	inline std::vector<std::string> GetScript() const
	{
		return script;
	}

protected:
	unsigned int line;
	std::vector<std::string> script;
};
