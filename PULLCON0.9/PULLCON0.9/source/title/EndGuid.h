#pragma once
#include "appframe.h"
#include "ActorTitle.h"
#include "../mode/ModeTitle.h"
class EndGuid:public ActorTitle
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
	EndGuid( ApplicationBase& game,int laysr,ModeTitle& mode );
	~EndGuid();
	virtual Type GetType()//自分が何者か
	{
		return Type::KENDGUID;
	}

	void	Initialize();//初期化
	bool	Update();
	bool	Draw();

private:
	int		_cg;		// 画像
};

