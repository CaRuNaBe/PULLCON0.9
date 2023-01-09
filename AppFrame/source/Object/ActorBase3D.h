#pragma once

#include "../Math/math.h"
#include "ObjectBase.h"
using namespace math;
class ActorBase : public ObjectBase {
	typedef ObjectBase base;
public:
	ActorBase();
	virtual ~ActorBase();

	enum Type {  // 種別の列挙型
		kBase,     // 0 アクター
		kPlayer,   // 1 プレイヤー
		kBullet,   // 2 弾丸
		kEnemyAAA, // 3 対空砲
	};
	virtual Type GetType() = 0;

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);

	virtual void Damage(ModeBase& mode) {}

	// 座標の設定
	void SetPosition(const vector4& pos) { _vPos = pos; }
	void SetPosition(float x, float y, float z) { _vPos.x = x; _vPos.y = y; _vPos.z = z; }
	// 向きベクトルの設定
	void SetDir(const vector4& dir) { _vDir = dir; }
	void SetDir(float x, float y, float z) { _vDir.x = x; _vDir.y = y; _vDir.z = z; }
public:
	vector4 _vPos;
	vector4 _vDir;

	float _speed;

	int _cnt;  // 動作カウント
	int _ST;   // 生存時間
};