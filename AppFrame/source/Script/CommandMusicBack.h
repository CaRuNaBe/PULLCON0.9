/*****************************************************************//**
 * \file   command_musicbag.h
 * \brief 'fg' スクリプトを処理するクラス定義
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "CommandBase.h"
#include <string>
class CommandMusicBack :public CommandBase
{
public:
	CommandMusicBack( unsigned int line , const std::vector<std::string>& script );
	CommandMusicBack( const CommandMusicBack& ) = default;
	CommandMusicBack( CommandMusicBack&& ) noexcept = default;

	virtual ~CommandMusicBack() = default;

	CommandMusicBack& operator=( const CommandMusicBack& right ) = default;
	CommandMusicBack& operator=( CommandMusicBack&& right ) noexcept = default;

	bool Check () override;

	inline std::string GetLabel () const
	{
		return script [ 1 ];
	}

	inline int GetMgHandle () const
	{
		return mghandle;
	}
	inline void SetMgHandle ( const int handle )
	{
		this->mghandle = handle;
	}

private:
	int mghandle;
};

