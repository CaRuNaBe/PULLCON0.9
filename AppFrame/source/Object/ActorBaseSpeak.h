#pragma once
#include "ObjectBase.h"
#include "../Math/math.h"
class ActorBaseSpeak:public ObjectBase
{
	using base = ObjectBase;
public:
	ActorBaseSpeak( ApplicationBase& game,ModeBase& mode );
	virtual ~ActorBaseSpeak();

	virtual void	Init();/*初期化*/
	virtual bool	Update();//
	virtual bool	Draw();


protected:
	math::Vector2	_pos;		// 座標
	int		_cnt;		// 動作カウンタ
};

