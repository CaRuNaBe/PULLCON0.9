#pragma once
#include "appframe.h"

class StageObject:
    public ActorBase3D
{
	using base = ActorBase3D;
public:
	StageObject( ApplicationBase& game,ModeBase& mode,int objectid,int collision ,int pieces_coll);
	virtual ~StageObject();
	virtual Type GetType()
	{
		return Type::kStageObject;
	}
	// ステージオブジェクトの状態
	enum class State {
		NUM, //初期状態
		STATE,//プレイアブル状態
	};

	virtual void Init();
	virtual bool Update(  );
	virtual bool Draw( );

	void AddCollision();

protected:
	State  _stateStageObject;

	int    _iPiecesColl;
	int    _handle;
};

