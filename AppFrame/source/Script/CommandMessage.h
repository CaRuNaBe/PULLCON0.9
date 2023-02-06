//!
//! @file command_message.h
//!
//! @brief 'm' スクリプトを処理するクラス定義
//!
#pragma once

#include "CommandBase.h"
#include "rect.h"
#include <string>

class CommandMessage final : public CommandBase
{
public:
	CommandMessage ( unsigned int line , const std::vector<std::string>& script );
	CommandMessage ( const CommandMessage& ) = default;
	CommandMessage ( CommandMessage&& ) noexcept = default;

	virtual ~CommandMessage () = default;

	CommandMessage& operator=( const CommandMessage& right ) = default;
	CommandMessage& operator=( CommandMessage&& right ) noexcept = default;

	bool Check () override;

	inline void Initialize (scliptmath::Rect&& area , const int goal )
	{
		this->area = area;
		right_goal = goal;
	}

	inline std::string Whospeak () const
	{
		return script [ 1 ];
	}

	inline std::string GetMessageA () const
	{
		return script [ 2 ];
	}
	inline const scliptmath::Rect& GetArea () const
	{
		return area;
	}
	inline int GetRightGoal () const
	{
		return right_goal;
	}

	inline void UpdateAreaRight ( const int right )
	{
		area.right = right;
	}

private:
	scliptmath::Rect area;
	int right_goal;
};
