#pragma once
#include "appframe.h"
#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
class Bullet : public ActorBase3D{
	typedef ActorBase3D base;
public:
	Bullet( ApplicationBase& game,ModeMainGame& mode);
	virtual ~Bullet();
	virtual Type GetType() { return Type::kBullet; }

	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();

	int    _iType;
protected:

	int    _handleBlue;
	int    _handlePurple;
	int    _handleYellow;
	int    _handle;
};

