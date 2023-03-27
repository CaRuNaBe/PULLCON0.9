/*****************************************************************//**
 * \file   command_movieplay.cpp
 * \brief   've' スクリプトを処理するクラス実装
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#include "CommandMoviePlay.h"
namespace
{
	constexpr size_t SCRIPT_NUM = 6;
}

CommandMoviePlay::CommandMoviePlay( unsigned int line,const std::vector<std::string>& script )
	: CommandBase( line,script )
{
	mvhandle = 0;
	posi_x1 = 0;
	posi_y1 = 0;
	posi_x2 = 0;
	posi_y2 = 0;
}

bool CommandMoviePlay::Check()
{
	const auto size = script.size();

	if ( size != SCRIPT_NUM )
	{
		return false;
	}
	if ( !string::ToInt( script[1],posi_x1 ) )
	{
		return false;
	}
	if ( !string::ToInt( script[2],posi_y1 ) )
	{
		return false;
	}
	if ( !string::ToInt( script[3],posi_x2 ) )
	{
		return false;
	}
	if ( !string::ToInt( script[4],posi_y2 ) )
	{
		return false;
	}
	return true;
}