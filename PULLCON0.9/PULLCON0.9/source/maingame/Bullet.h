#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
class Bullet : public ActorMainGame
{
public:
	Bullet(ApplicationBase& game, int layer, ModeMainGame& mode);
	virtual ~Bullet();
	virtual Type GetType()
	{
		return Type::kBullet;
	}

	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();

protected:
	int    _handleBlue;
	int    _handlePurple;
	int    _handleYellow;
	int    _handle;
};

