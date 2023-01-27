#pragma once
#include "appframe.h"


class EnemyAAA : public ActorBase3D {
	typedef ActorBase3D base;
public:
	EnemyAAA();
	virtual ~EnemyAAA();
	virtual Type GetType() { return Type::kEnemyAAA; }
	// �΋�C�̏��
	enum class State
	{
		PLAY,//�v���C�A�u�����
		EVENT,//�C�x���g���
		WEAPON//���퉻
	};

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);

	virtual void Damage(ModeBase& mode);
	void AddBullet(ModeBase& mode);

protected:
	State   _stateAAA;

	int    _iType;
	int    _iPossession;
	float  _fAxialY;  // Y����](�x���@)	
	float  _fAxialX;  // X����](�x���@)

	int    _handle_body;
	int    _handle_turret;

};
