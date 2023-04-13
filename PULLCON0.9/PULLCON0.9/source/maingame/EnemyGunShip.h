#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
class EnemyGunShip :public ActorMainGame
{
public:
	EnemyGunShip(ApplicationBase& game, int layer, ModeMainGame& mode, float _radius);
	virtual ~EnemyGunShip();
	virtual Type GetType()
	{
		return Type::kEnemyGunShip;
	}
	// ƒKƒ“ƒVƒbƒv‚Ìó‘Ô
	enum class State
	{
		NUM, //‰Šúó‘Ô
		WAIT,//‘Ò‹@ó‘Ô
		PLAY,//Œ}Œ‚‘Ì§
	};
	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void AddBullet();

protected:
	State   _stateClearObject;

	vector4 _vObjective;  // ‰~‹O“¹’†SÀ•W

	int    _handle;
	float radius;
};

