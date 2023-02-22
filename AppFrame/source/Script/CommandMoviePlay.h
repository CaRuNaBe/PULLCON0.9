/*****************************************************************//**
 * \file   command_movieplay.h
 * \brief  've' スクリプトを処理するクラス定義
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "CommandBase.h"
#include "ScriptsString.h"
class CommandMoviePlay:public CommandBase
{
public:
	CommandMoviePlay( unsigned int line,const std::vector<std::string>& script );
	CommandMoviePlay( const  CommandMoviePlay& ) = default;
	CommandMoviePlay( CommandMoviePlay&& ) noexcept = default;

	virtual ~CommandMoviePlay() = default;

	CommandMoviePlay& operator=( const  CommandMoviePlay& right ) = default;
	CommandMoviePlay& operator=( CommandMoviePlay&& right ) noexcept = default;

	bool Check() override;

	inline std::string GetLabel() const
	{
		return script[3];
	}

	inline int GetMvHandle() const
	{
		return mvhandle;
	}
	inline void SetMvHandle( const int handle )
	{
		this->mvhandle = handle;
	}
	inline int GetPosiX() const
	{
		return posi_x;
	}
	inline int GetPosiY() const
	{
		return posi_y;
	}
private:
	int mvhandle;
	int posi_x;
	int posi_y;
};

