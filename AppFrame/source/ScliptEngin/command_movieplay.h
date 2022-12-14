/*****************************************************************//**
 * \file   command_movieplay.h
 * \brief  've' スクリプトを処理するクラス定義
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "command_base.h"
class CommandMovieplay :public CommandBase
{
public:
	CommandMovieplay ( unsigned int line , const std::vector<std::string>& script );
	CommandMovieplay ( const  CommandMovieplay& ) = default;
	CommandMovieplay ( CommandMovieplay&& ) noexcept = default;

	virtual ~CommandMovieplay () = default;

	CommandMovieplay& operator=( const  CommandMovieplay& right ) = default;
	CommandMovieplay& operator=( CommandMovieplay&& right ) noexcept = default;

	bool Check () override;

	inline std::string GetLabel () const
	{
		return script [ 1 ];
	}

	inline int GetMvHandle () const
	{
		return mvhandle;
	}
	inline void SetMvHandle ( const int handle )
	{
		this->mvhandle = handle;
	}

private:
	int mvhandle;
};

