#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
#include <string>
#include <sstream>
#include <array>
class EnemyAAA : public ActorMainGame
{
public:
	EnemyAAA(ApplicationBase& game, int layer, ModeMainGame& mode, int min_id, int max_id, int pile_num, float scale, vector4 _vPosi);
	virtual ~EnemyAAA();
	virtual Type GetType()
	{
		return Type::kEnemyAAA;
	}
	// 対空砲の状態
	enum class State
	{
		NUM,//地下の対空砲
		PLAY,//プレイアブル状態
		EVENT,//イベント状態
		WEAPON//兵器化
	};

	virtual void Initialize(int pile_num, vector4 _vPosi, float scale);
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void AddBullet(const int& theta_split_num, const int& phi_split_num, const int& theta_degree_lower, const int& theta_degree_upper, const int& phi_degree_lower, const int& phi_degree_upper);
	void AddPieces(int min_id, int max_id, int pile_num, float scale);
	void GetSearch();
	void SetDamage();
	void SetStateAAA();

	void SetAxialX(float _x_rad)
	{
		_fAxialX = _x_rad;
	}
	void SetAxialY(float _y_rad)
	{
		_fAxialY = _y_rad;
	}
	void SetType(int _aim_player)
	{
		_iEnemyType = _aim_player;
	}
protected:
	State   _stateAAA;

	int    _iEnemyType;    // タイプ 0,追尾式 1,固定式
	int    _iSurvivalTime; // 射撃する弾の生存時間
	int    _iPossession;   // 対空砲パーツの所有数
	float  _fAxialY;       // Y軸回転(度数法)	
	float  _fAxialX;       // X軸回転(度数法)
	bool   _get;           // プレイヤーを探知したか

	int    _handle_body;
	int    _handle_turret;

	int AAA_ID;
	std::vector<int>bullet_state;

};
