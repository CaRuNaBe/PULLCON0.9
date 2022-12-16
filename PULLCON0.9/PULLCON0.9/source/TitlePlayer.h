#pragma once
#include "ActorBase2d.h"
class TitlePlayer:public ActorBase2d
{
	using Actor2d = ActorBase2d;
public:
	/**
	 * �v���C���[�̏��.
	 */
	enum class State
	{
		IDLING,//�ҋ@
		MOVING,//�ړ�
		PULLING//������
	};
	TitlePlayer();
	~TitlePlayer();
	virtual Type	GetType()
	{
		return Type::KPLAYER;
	}

	void	Init();
	bool	Update(ApplicationBase& game);
	bool	Draw(ApplicationBase& game);

private:
	int		_cg;		// �摜

};

