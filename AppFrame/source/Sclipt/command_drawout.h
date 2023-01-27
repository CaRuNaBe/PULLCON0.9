/*****************************************************************//**
 * \file   command_drawout.h
 * \brief   'do'  スクリプトを処理するクラス定義
 *
 *
 * \author 阿部健太郎
 * \date   August 2022
 *********************************************************************/
#pragma once
#include "command_base.h"
#include <string>
class CommandDrawout :public CommandBase
{
public:
	CommandDrawout ( unsigned int line , const std::vector<std::string>& script );
	CommandDrawout ( const CommandDrawout& ) = default;
	CommandDrawout ( CommandDrawout&& ) noexcept = default;

	virtual ~CommandDrawout () = default;

	CommandDrawout& operator=( const CommandDrawout& right ) = default;
	CommandDrawout& operator=( CommandDrawout&& right ) noexcept = default;

	bool Check () override;

	inline std::string GetLabel () const
	{
		return script [ 5 ];
	}

	inline int GetIndex () const
	{
		return index;
	}
	inline int GetX () const
	{
		return x;
	}
	inline int GetY () const
	{
		return y;
	}
	inline int GetHandle () const
	{
		return handle;
	}
	inline void SetHandle ( const int handle )
	{
		this->handle = handle;
	}

	inline int GetoutCount () const
	{
		return out_count;
	}

	inline double GetDrawAlphaout ()const
	{
		return _DrawAlphaout;
	}

	inline void SetDrawAlphaout ( double new_DrawAlphaout )
	{
		this->_DrawAlphaout = new_DrawAlphaout;
	};

	inline bool GetDrawcomplete ()
	{
		return isdrawoutcomplete;
	}

	inline void SetDrawcomplete ( bool completedraw )
	{
		this->isdrawoutcomplete = completedraw;
	}

private:
	int index;
	int x;
	int y;
	int out_count;
	int handle;
	double _DrawAlphaout;
	bool isdrawoutcomplete;
};

