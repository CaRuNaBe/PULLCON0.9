#pragma once
#include "ObjectBase.h"
#include "../Math/math.h"
class ActorBaseSpeak:public ObjectBase
{
	using base = ObjectBase;
public:
	ActorBaseSpeak( ApplicationBase& game,ModeBase& mode );
	virtual ~ActorBaseSpeak();

	virtual void	Init();/*������*/
	virtual bool	Update();//
	virtual bool	Draw();
	virtual void SetPosi( math::Vector2	_pos )
	{
		this->_pos = _pos;
	}

protected:
	math::Vector2	_pos;		// ���W
	int		_cnt;		// ����J�E���^
};

