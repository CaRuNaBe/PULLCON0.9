#pragma once
#include "appframe.h"
#include "ActorBase2d.h"
#include "../mode/ModeTitle.h"
class EndGuid:public ActorBase2d
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
	EndGuid( ApplicationBase& game,ModeTitle& mode );
	~EndGuid();
	virtual Type	GetType()//自分が何者か
	{
		return Type::KENDGUID;
	}

	void	Init();//初期化
	bool	Update();
	bool	Draw();

private:
	int		_cg;		// 画像
};

