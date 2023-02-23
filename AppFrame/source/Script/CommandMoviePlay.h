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
		return script[5];
	}

	inline int GetMvHandle() const
	{
		return mvhandle;
	}
	inline void SetMvHandle( const int handle )
	{
		this->mvhandle = handle;
	}
	inline int GetPosiX1() const
	{
		return posi_x1;
	}
	inline int GetPosiY1() const
	{
		return posi_y1;
	}
	inline int GetPosiX2() const
	{
		return posi_x2;
	}
	inline int GetPosiY2() const
	{
		return posi_y2;
	}
private:
	int mvhandle;
	int posi_x1;
	int posi_y1;
	int posi_x2;
	int posi_y2;
};

