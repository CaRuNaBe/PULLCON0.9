#pragma once
#include "appframe.h"
class StartGuid:public ActorBase2d
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
	StartGuid( ApplicationBase& game,ModeBase& mode );
	~StartGuid();
	virtual Type	GetType()//自分が何者か
	{
		return Type::KGAMESTARTGUID;
	}

	void	Init();//初期化
	bool	Update();
	bool	Draw();

private:
	int		_cg;		// 画像
};

