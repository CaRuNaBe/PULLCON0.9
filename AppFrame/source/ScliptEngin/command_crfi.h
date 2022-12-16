/*****************************************************************//**
 * \file   command_crfi.h
 * \brief  'fi' スクリプトを処理するクラス定義
 *
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "command_base.h"
#include <string>
class CommandCrfi :public CommandBase
{
public:
	CommandCrfi ( unsigned int line , const std::vector<std::string>& script );
	CommandCrfi ( const CommandCrfi& ) = default;
	CommandCrfi ( CommandCrfi&& ) noexcept = default;

	virtual ~CommandCrfi () = default;

	CommandCrfi& operator=( const CommandCrfi& right ) = default;
	CommandCrfi& operator=( CommandCrfi&& right ) noexcept = default;

	bool Check () override;

	inline int GetinCount () const
	{
		return in_count;
	}
	inline int GetRed () const
	{
		return in_red;
	}
	inline int GetGreen () const
	{
		return in_green;
	}
	inline int GetBlue () const
	{
		return in_blue;
	}

private:
	int in_count;
	int in_red;
	int in_green;
	int in_blue;
};

