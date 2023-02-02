/*****************************************************************//**
 * @file   CommandCrFeedOut.h
 * @brief  'CrFeedout' スクリプトを処理するクラス定義
 *
 *
 * @author 阿部健太郎
 * @date   August 2022
 *********************************************************************/
#pragma once
#include "CommandBase.h"
#include <string>
class CommandCrFeedOut:public CommandBase
{
public:
	CommandCrFeedOut( unsigned int line , const std::vector<std::string>& script );
	CommandCrFeedOut( const CommandCrFeedOut& ) = default;
	CommandCrFeedOut( CommandCrFeedOut&& ) noexcept = default;

	virtual ~CommandCrFeedOut() = default;

	CommandCrFeedOut& operator=( const CommandCrFeedOut& right ) = default;
	CommandCrFeedOut& operator=( CommandCrFeedOut&& right ) noexcept = default;

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

