#pragma once
#include "appframe.h"
#include "ActorTitle.h"
#include "../mode/ModeTitle.h"
class EndLogo:public ActorTitle
{
		/**
	 * オブジェクトの状態.
	 */
	enum class State
	{
		IDLING,//待機
		PULLED//引っ張られている
	};
public:
	EndLogo( ApplicationBase& game,int layer,ModeTitle& mode );
	~EndLogo();
	virtual Type	GetType()//自分が何者か
	{
		return Type::KENDLOGO;
	}

	void	Initialize();//初期化
	bool	Update();
	bool	Draw();

private:
	int		_cg;		// 画像
};

