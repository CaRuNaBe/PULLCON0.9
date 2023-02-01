#pragma once
#include "appframe.h"


class EnemyAAA : public ActorBase3D {
	typedef ActorBase3D base;
public:
	EnemyAAA();
	virtual ~EnemyAAA();
	virtual Type GetType() { return Type::kEnemyAAA; }
	// 対空砲の状態
	enum class State
	{
		NUM,//地下の対空砲
		PLAY,//プレイアブル状態
		EVENT,//イベント状態
		WEAPON//兵器化
	};

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);

	virtual void Damage(ModeBase& mode);
	void AddBullet(ModeBase& mode);
	void AddPieces(ModeBase& mode);

protected:
	State   _stateAAA;

	int    _iType;  // タイプ 0,追尾式 1,固定式
	int    _iPossession;  // 対空砲パーツの所有数
	int    _iPart;  // 地下の対空砲パーツの番号
	float  _fAxialY;  // Y軸回転(度数法)	
	float  _fAxialX;  // X軸回転(度数法)
	bool   _have;  // 持っているか

	int    _handle_body;
	int    _handle_turret;

};
