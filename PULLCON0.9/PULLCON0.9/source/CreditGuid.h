#pragma once
#include "appframe.h"
class CreditGuid: public ActorBase2d
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
	CreditGuid();
	~CreditGuid();
	virtual Type	GetType()//自分が何者か
	{
		return Type::KCREDITGUID;
	}

	void	Init();//初期化
	bool	Update( ApplicationBase& game,ModeBase& mode );
	bool	Draw( ApplicationBase& game,ModeBase& mode );

private:
	int		_cg;		// 画像
};
