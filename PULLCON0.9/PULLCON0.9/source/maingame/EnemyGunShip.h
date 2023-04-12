#pragma once
#include "appframe.h"
#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
class EnemyGunShip :
	public ActorBase3D {
	using base = ActorBase3D;
public:
	EnemyGunShip(ApplicationBase& game, ModeMainGame& mode, float _radius);
	virtual ~EnemyGunShip();
	virtual Type GetType() { return Type::kClearObject; }
	// ƒKƒ“ƒVƒbƒv‚Ìó‘Ô
	enum class State {
		NUM, //‰Šúó‘Ô
		WAIT,//‘Ò‹@ó‘Ô
		PLAY,//Œ}Œ‚‘Ì§
	};
	virtual void Init();
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

