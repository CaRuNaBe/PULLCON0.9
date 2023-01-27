/*****************************************************************//**
 * \file   command_musicbag.h
 * \brief 'fg' スクリプトを処理するクラス定義
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "command_base.h"
#include <string>
class CommandMusicbag :public CommandBase
{
public:
	CommandMusicbag ( unsigned int line , const std::vector<std::string>& script );
	CommandMusicbag ( const CommandMusicbag& ) = default;
	CommandMusicbag ( CommandMusicbag&& ) noexcept = default;

	virtual ~CommandMusicbag () = default;

	CommandMusicbag& operator=( const CommandMusicbag& right ) = default;
	CommandMusicbag& operator=( CommandMusicbag&& right ) noexcept = default;

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

