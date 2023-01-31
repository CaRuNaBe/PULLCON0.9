/*****************************************************************//**
 * \file   CommandCrFeedIn.h
 * \brief  'CrFeedIn' スクリプトを処理するクラス定義
 *
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "CommandBase.h"
#include <string>
class CommandCrFeedIn:public CommandBase
{
public:
	CommandCrFeedIn( unsigned int line , const std::vector<std::string>& script );
	CommandCrFeedIn( const CommandCrFeedIn& ) = default;
	CommandCrFeedIn( CommandCrFeedIn&& ) noexcept = default;

	virtual ~CommandCrFeedIn() = default;

	CommandCrFeedIn& operator=( const CommandCrFeedIn& right ) = default;
	CommandCrFeedIn& operator=( CommandCrFeedIn&& right ) noexcept = default;

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

