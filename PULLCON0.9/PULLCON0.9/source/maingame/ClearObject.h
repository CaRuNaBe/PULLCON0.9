#pragma once
#include "appframe.h"
class ClearObject:
	public ActorBase3D
{
	using base = ActorBase3D;
public:
	ClearObject( ApplicationBase& game,ModeBase& mode,float _radius );
	virtual ~ClearObject();
	virtual Type GetType()
	{
		return Type::kClearObject;
	}
	// プレイヤーの状態
	enum class State
	{
		NUM, //初期状態
		WAIT,//待機状態
		PLAY,//迎撃体制
	};
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void AddBullet();

protected:
	State   _stateClearObject;  // ガンシップステータス

	vector4 _vObjective;  // 円軌道中心座標

	int    _handle;
	float radius;
};

