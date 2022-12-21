/*****************************************************************//**
 * \file   StartLogo.h
 * \brief  
 * 
 * \author ˆ¢•”Œ’‘¾˜Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include "appframe.h"
class StartLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	StartLogo();
	~StartLogo();
	virtual Type	GetType()//©•ª‚ª‰½Ò‚©
	{
		return Type::KGAMESTARTLOGO;
	}

	void	Init();//‰Šú‰»
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );

private:
	int		_cg;		// ‰æ‘œ

};