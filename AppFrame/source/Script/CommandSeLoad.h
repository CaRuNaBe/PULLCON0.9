/*****************************************************************//**
 * \file   command_seload.h
 * \brief  'im' スクリプトを処理するクラス定義
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "CommandBase.h"
#include <string>
class CommandSeLoad:public CommandBase
{
public:
	CommandSeLoad( unsigned int line,const std::vector<std::string>& script );
	CommandSeLoad( CommandSeLoad& ) = default;
	CommandSeLoad( CommandSeLoad&& ) noexcept = default;

	virtual ~CommandSeLoad() = default;

	CommandSeLoad& operator=( CommandSeLoad const& right ) = default;
	CommandSeLoad& operator=( CommandSeLoad&& right ) = default;

	bool Check() override;

	inline std::string GetLabel() const
	{
		return script[1];
	}
	inline int GetHandle() const
	{
		return sehandle;
	}

private:
	int sehandle;
};

