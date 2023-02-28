#pragma once
#include "appframe.h"
#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
class AreaEnemySpawn:public ActorBase3D
{
	using base = ActorBase3D;
public:
	AreaEnemySpawn( ApplicationBase& game,ModeMainGame& mode,  int spawnfream,int typeenemy );
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

	virtual void Damage();
	void  AddEnemyColumn();
	void  AddEnemyKobae();
protected:
	State  _stateEnemySpawn;

	int  _iSpawnFream;
	int  _iEnemyType;
	bool _isAddKobae;

	int _handle;
	int _handleSky;
	int _handleKobae;
};

