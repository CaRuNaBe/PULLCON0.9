//!
//! @file command_image.h
//!
//! @brief 'i' スクリプトを処理するクラス定義
//!
#pragma once

#include "CommandBase.h"
#include <string>

class CommandImageLoad final : public CommandBase
{
public:
	CommandImageLoad( unsigned int line , const std::vector<std::string>& script );
	CommandImageLoad( const CommandImageLoad& ) = default;
	CommandImageLoad( CommandImageLoad&& ) noexcept = default;

	virtual ~CommandImageLoad() = default;

	CommandImageLoad& operator=( CommandImageLoad const& right ) = default;
	CommandImageLoad& operator=( CommandImageLoad&& right ) = default;

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
