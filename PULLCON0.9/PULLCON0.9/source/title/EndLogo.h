#pragma once
#include "appframe.h"
#include "ActorBase2d.h"
#include "../mode/ModeTitle.h"
class EndLogo:public ActorBase2d
{
	using Actor2d = ActorBase2d;
		/**
	 * オブジェクトの状態.
	 */
	enum class State
	{
		IDLING,//待機
		PULLED//引っ張られている
	};
public:
	EndLogo( ApplicationBase& game,ModeTitle& mode );
	~EndLogo();
	virtual Type	GetType()//自分が何者か
	{
		return Type::KENDLOGO;
	}

	void	Init();//初期化
	bool	Update();
	bool	Draw();

private:
	int		_cg;		// 画像
};

