//!
//! @file command_image.h
//!
//! @brief 'i' スクリプトを処理するクラス定義
//!
#pragma once

#include "command_base.h"
#include <string>

class CommandImageload final : public CommandBase
{
public:
	CommandImageload ( unsigned int line , const std::vector<std::string>& script );
	CommandImageload ( const CommandImageload& ) = default;
	CommandImageload ( CommandImageload&& ) noexcept = default;

	virtual ~CommandImageload () = default;

	CommandImageload& operator=( CommandImageload const& right ) = default;
	CommandImageload& operator=( CommandImageload&& right ) = default;

	bool Check () override;

	inline std::string GetLabel () const
	{
		return script [ 1 ];
	}
	inline int GetHandle () const
	{
		return handle;
	}

private:
	int handle;
};
