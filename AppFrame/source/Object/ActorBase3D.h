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
		kClearObject,   // 5 最終目標
		kSkySphere,     // 6 スカイスフィア
		kGameStage,     // 7 ゲームステージ
		kSupplyEria,    // 8 補給地点
		kEffect,        // n エフェクト
	};
	virtual Type GetType() = 0;

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual void	UpdateCollision();
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);
	virtual void	DrawCollision(vector4 color);
	virtual void	DrawCollisionEvent(vector4 color);
	virtual void	DrawCollisionSearch(vector4 color);

	virtual bool	IsHitObject(ActorBase3D& object);	// 指定のオブジェクトと当たっているか
	virtual bool	IsHitEvent(ActorBase3D& object);	// イベントスフィアと当たっているか
	virtual bool	IsSearch(ActorBase3D& object);	  // サーチスフィアと当たっているか

	virtual void Damage(ModeBase& mode) {}

	virtual Sphere& GetCollision() { return _collision; }
	virtual Sphere& GetCollisionEvent() { return _collisionEvent; }
	virtual Sphere& GetCollisionSearch() { return _collisionSearch; }

	// 座標の設定
	void SetPosition(const vector4& pos) { _vPos = pos; }
	void SetPosition(float x, float y, float z) { _vPos.x = x; _vPos.y = y; _vPos.z = z; }
	virtual vector4& GetPosition() { return _vPos; }
	// 向きベクトルの設定
	void SetDir(const vector4& dir) { _vDir = dir; }
	void SetDir(float x, float y, float z) { _vDir.x = x; _vDir.y = y; _vDir.z = z; }

public:
	vector4 _vPos;   // 位置
	vector4 _vEvent;   // イベント位置
	vector4 _vRelation;   // 位置関係
	vector4 _vTarget;   // 目標位置
	vector4 _vDir;   // 向き

	Sphere  _collision;   // 球判定
	Sphere  _collisionEvent;   // イベント判定
	Sphere  _collisionSearch;   // 索敵判定

	int   _iFuel;    // 燃料
	int   _iLife;    // ライフ
	int   _iDamage;  // 与えるダメージ
	int   _iPieces;  // 個数
	float _fSpeed;   // 速度
	float _fScale;   // 大きさ
	float _fRotatX;  // X軸回転
	float _fRotatY;  // Y軸回転
	bool  _coll;   // コリジョン判定をするか
	bool  _overlap;   // 判定が重なったか
	bool  _event;   // イベント判定と重なったか
	bool  _pull;    // イベント
	bool  _finish;   // イベント完了
	bool  _fire;    // 発砲

	int _cnt;  // 動作カウント
	int _CT;   // クールタイム
	int _ST;   // 生存時間
};