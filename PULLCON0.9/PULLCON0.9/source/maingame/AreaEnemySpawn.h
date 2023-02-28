#pragma once
#include "appframe.h"

class AreaEnemySpawn :public ActorBase3D {
	using base = ActorBase3D;
public:
	AreaEnemySpawn(ApplicationBase& game, ModeBase& mode, int spawnfream, int typeenemy);
	virtual ~AreaEnemySpawn();
	virtual Type GetType() { return Type::kAreaEnemySpawn; }
	// ‹ó’†”òsŠî’n‚Ìó‘Ô
	enum class State {
		NUM, //‰Šúó‘Ô
		WAIT,//‘Ò‹@ó‘Ô
	};
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

protected:
	State  _stateEnemySpawn;

	int spawn_fream;
	int type_enemy;
};

