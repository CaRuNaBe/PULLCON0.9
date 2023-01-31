#pragma once
#include "appframe.h"


class EnemyAAA: public ActorBase3D
{
	typedef ActorBase3D base;
public:
	EnemyAAA( ApplicationBase& game,ModeBase& mode,int min_id,int max_id,int pile_num );
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
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage( );
	void AddBullet(  );

protected:
	State   _stateAAA;

	int    _handle_body;
	int    _handle_turret;

};
