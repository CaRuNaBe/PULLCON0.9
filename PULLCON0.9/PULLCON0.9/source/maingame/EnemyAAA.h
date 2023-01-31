#pragma once
#include "appframe.h"


class EnemyAAA: public ActorBase3D
{
	typedef ActorBase3D base;
public:
	EnemyAAA( int min_id,int max_id,int pile_num );
	virtual ~EnemyAAA();
	virtual Type GetType()
	{
		return Type::kEnemyAAA;
	}
// �΋�C�̏��
	enum class State
	{
		PLAY,//�v���C�A�u�����
		EVENT,//�C�x���g���
		WEAPON//���퉻
	};

	virtual void Init();
	virtual bool Update( ApplicationBase& game,ModeBase& mode );
	virtual bool Draw( ApplicationBase& game,ModeBase& mode );

	virtual void Damage( ModeBase& mode );
	void AddBullet( ModeBase& mode );

protected:
	State   _stateAAA;

	int    _handle_body;
	int    _handle_turret;

};
