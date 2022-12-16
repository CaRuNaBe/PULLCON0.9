#pragma once
#include "appframe.h"
using namespace math;
class ActorBase2d:public ObjectBase
{
	using base = ObjectBase;
public:
	enum class Type
	{  // 種別の列挙型
		KBASE,			// 0 アクター
		KPLAYER,		// 1 プレイヤー
		KTITLELOGO,	// 2 タイトルロゴ
		KGAMESTARTLOGO,			// 3 ゲームスタートロゴ
		KCREDITLOGO,	// 4 クレジットロゴ
		KENDLOGO,		// 5 ゲーム終了ロゴ
	};
	virtual Type GetType() = 0;

	ActorBase2d();
	virtual ~ActorBase2d();

	virtual void	Init();
	virtual bool	Update(ApplicationBase& game);
	virtual void	UpdateCollision();
	virtual bool	Draw(ApplicationBase& game);
	virtual void	DrawCollision();

	virtual AABB& GetCollision()
	{
		return _collision;
	}
	virtual bool	IsDead()
	{
		return _dead;
	}
	virtual void	Dead()
	{
		_dead = true;
	}
	virtual Vector2& GetPosition()
	{
		return _pos;
	}
	virtual void	SetPosition(Vector2 pos)
	{
		_pos = pos;
	}
	virtual Vector2& GetSize()
	{
		return _size;
	}
	virtual void	SetSize(Vector2 size)
	{
		_size = size;
	}
	virtual bool	IsHitObject(ActorBase2d& object);	// 指定のオブジェクトと当たっているか？
protected:
	Vector2	_pos;		// 座標
	Vector2 _size;		// 大きさ
	float	_spd;		// 移動速度
	AABB	_collision;	// 当たり判定用矩形
	Vector2	_colPos,_colSize;	// 当たり判定位置サイズ(_posからの差分)

	int		_cnt;		// 動作カウンタ
};

/*
// ObjectBaseクラス
class ObjectBase
{
public:
	ObjectBase(Game& game,ModeBase& mode);
	virtual ~ObjectBase();

	enum class Type
	{  // 種別の列挙型
		kBase,			// 0 アクター
		kPlayer,		// 1 プレイヤー
		kBackground,	// 2 背景
		kEnemy,			// 3 エネミー
		kPlayerBullet,	// 4 プレイヤーの弾
		kEffect,		// 5 エフェクト
	};
	virtual Type	GetType() = 0;

	virtual void	Init();
	virtual void	Update();
	virtual void	UpdateCollision();
	virtual void	Render();
	virtual void	DrawCollision();
	virtual AABB& GetCollision()
	{
		return _collision;
	}
	virtual void	Damage();
	virtual bool	IsDead()
	{
		return _dead;
	}
	virtual void	Dead()
	{
		_dead = true;
	}
	virtual Vector2& GetPosition()
	{
		return _pos;
	}
	virtual void	SetPosition(Vector2 pos)
	{
		_pos = pos;
	}
	virtual Vector2& GetSize()
	{
		return _size;
	}
	virtual void	SetSize(Vector2 size)
	{
		_size = size;
	}
	virtual bool	IsHitObject(ObjectBase& object);	// 指定のオブジェクトと当たっているか？

protected:
	Game& _game;
	ModeBase& _mode;
	bool	_dead;

	Vector2	_pos;		// 座標
	Vector2 _size;		// 大きさ
	float	_spd;		// 移動速度
	AABB	_collision;	// 当たり判定用矩形
	Vector2	_colPos,_colSize;	// 当たり判定位置サイズ(_posからの差分)
	int		_hit_noCnt;	// カウンタが1以上の場合は当たり判定しない

	int		_cnt;		// 動作カウンタ
};
*/