/*****************************************************************//**
 * \file   command_crfi.h
 * \brief  'fo' スクリプトを処理するクラス定義
 *
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "command_base.h"
#include <string>
class CommandCrfo :public CommandBase
{
public:
	CommandCrfo ( unsigned int line , const std::vector<std::string>& script );
	CommandCrfo ( const CommandCrfo& ) = default;
	CommandCrfo ( CommandCrfo&& ) noexcept = default;

	virtual ~CommandCrfo () = default;

	CommandCrfo& operator=( const CommandCrfo& right ) = default;
	CommandCrfo& operator=( CommandCrfo&& right ) noexcept = default;

	bool Check () override;

	inline int GetoutCount () const
	{
		return out_count;
	}
	inline int GetRed () const
	{
		return out_red;
	}
	inline int GetGreen () const
	{
		return out_green;
	}
	inline int GetBlue () const
	{
		return out_blue;
	}

private:
	int out_count;
	int out_red;
	int out_green;
	int out_blue;

};

