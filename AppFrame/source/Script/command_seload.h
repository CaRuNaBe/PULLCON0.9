/*****************************************************************//**
 * \file   command_seload.h
 * \brief  'im' スクリプトを処理するクラス定義
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "command_base.h"
#include <string>
class CommandSeload :public CommandBase
{
public:
	CommandSeload ( unsigned int line , const std::vector<std::string>& script );
	CommandSeload ( CommandSeload& ) = default;
	CommandSeload ( CommandSeload&& ) noexcept = default;

	virtual ~CommandSeload () = default;

	CommandSeload& operator=( CommandSeload const& right ) = default;
	CommandSeload& operator=( CommandSeload&& right ) = default;

	bool Check () override;

	inline std::string GetLabel () const
	{
		return script [ 1 ];
	}
	inline int GetHandle () const
	{
		return sehandle;
	}

private:
	int sehandle;
};

