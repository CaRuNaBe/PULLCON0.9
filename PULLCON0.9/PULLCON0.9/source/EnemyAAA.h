#pragma once
#include "appframe.h"


class EnemyAAA : public ActorBase3D {
	typedef ActorBase3D base;
public:
	EnemyAAA();
	virtual ~EnemyAAA();
	virtual Type GetType() { return Type::kEnemyAAA; }

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);

	virtual void Damage(ModeBase& mode);
	void AddBullet(ModeBase& mode);

protected:

	vector4 _vTarget;
	float  _rotatX;
	float  _rotatY;
	int    _handle_body;
	int    _handle_turret;

};
