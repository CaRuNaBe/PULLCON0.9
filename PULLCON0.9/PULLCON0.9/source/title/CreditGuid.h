#pragma once
#include "appframe.h"
#include "ActorTitle.h"
#include "../mode/ModeTitle.h"
class CreditGuid: public ActorTitle
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
	CreditGuid( ApplicationBase& game,int layer,ModeTitle& mode );
	~CreditGuid();
	virtual Type	GetType()//自分が何者か
	{
		return Type::KCREDITGUID;
	}

	void	Initialize();//初期化
	bool	Update( );
	bool	Draw( );

private:
	int		_cg;		// 画像
};
