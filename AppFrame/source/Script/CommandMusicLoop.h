/*****************************************************************//**
 * \file   command_musicloop.h
 * \brief  'bg' スクリプトを処理するクラス定義
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "CommandBase.h"
#include <string>
class CommandMusicLoop : public CommandBase
{
public:
	CommandMusicLoop( unsigned int line , const std::vector<std::string>& script );
	CommandMusicLoop( const CommandMusicLoop& ) = default;
	CommandMusicLoop( CommandMusicLoop&& ) noexcept = default;

	virtual ~CommandMusicLoop() = default;

	CommandMusicLoop& operator=( const CommandMusicLoop& right ) = default;
	CommandMusicLoop& operator=( CommandMusicLoop&& right ) noexcept = default;

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

