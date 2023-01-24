/*****************************************************************//**
 * \file   command_musicloop.h
 * \brief  'bg' スクリプトを処理するクラス定義
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "command_base.h"
#include <string>
class CommandMusicloop : public CommandBase
{
public:
	CommandMusicloop ( unsigned int line , const std::vector<std::string>& script );
	CommandMusicloop ( const CommandMusicloop& ) = default;
	CommandMusicloop ( CommandMusicloop&& ) noexcept = default;

	virtual ~CommandMusicloop () = default;

	CommandMusicloop& operator=( const CommandMusicloop& right ) = default;
	CommandMusicloop& operator=( CommandMusicloop&& right ) noexcept = default;

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

