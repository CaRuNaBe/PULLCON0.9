#pragma once

#include "../Math/math.h"
#include "ObjectBase.h"
using namespace math;
class ActorBase3D : public ObjectBase {
	typedef ObjectBase base;
public:
	ActorBase3D();
	virtual ~ActorBase3D();

	enum class Type {  // 種別の列挙型
		kBase,          // 0 アクター
		kPlayer,        // 1 プレイヤー
		kBullet,        // 2 弾丸
		kEnemyAAA,      // 3 対空砲
	};
	virtual Type GetType() = 0;

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual void	UpdateCollision();
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);
	virtual void	DrawCollision();
	virtual bool	IsHitObject(ActorBase3D& object);	// 指定のオブジェクトと当たっているか

	virtual void Damage(ModeBase& mode) {}

	virtual Sphere& GetCollision() { return _collision; }

	// 座標の設定
	void SetPosition(const vector4& pos) { _vPos = pos; }
	void SetPosition(float x, float y, float z) { _vPos.x = x; _vPos.y = y; _vPos.z = z; }
	// 向きベクトルの設定
	void SetDir(const vector4& dir) { _vDir = dir; }
	void SetDir(float x, float y, float z) { _vDir.x = x; _vDir.y = y; _vDir.z = z; }
public:
	vector4 _vPos;
	vector4 _vDir;

	Sphere  _collision;

	float _speed;

	int _cnt;  // 動作カウント
	int _CT;   // クールタイム
	int _ST;   // 生存時間
};