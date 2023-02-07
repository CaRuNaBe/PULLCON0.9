#pragma once
/*****************************************************************//**
 * \file   ActorBase2d.h
 * \brief  2D表示用オブジェクトベース
 *
 * \author 阿部健太郎
 * \date   December 2022
 *********************************************************************/
#include "../Math/math.h"
#include "ObjectBase.h"
using namespace math;
class ActorBase2d:public ObjectBase
{
	using base = ObjectBase;
public:
	enum class Type
	{
		// 種別の列挙型
		/** タイトル画面 */
		KBASE,			     // 0 アクター
		KPLAYER,		     // 1 プレイヤー
		KTITLELOGO,	     // 2 タイトルロゴ
		KGAMESTARTLOGO,	 // 3 ゲームスタートロゴ
		KGAMESTARTGUID,  // 4 ゲームスタートガイド
		KCREDITLOGO,	   // 5 クレジットロゴ
		KCREDITGUID,     // 6 クレジットガイド
		KENDLOGO,		     // 7 ゲーム終了ロゴ
		KENDGUID,        // 8 ゲーム終了ガイド
		/** ポーズ画面 */
		KPAUSELOGO,      // 9 ポーズ画面の表示ロゴ
		KDESCRIPTIONLOGO,// 10 ポーズ画面の操作説明ロゴ
		KRESTARTLOGO,    // 11 ポーズ画面の再スタートロゴ
		KRETURNTITLELOGO,    // 12 ポーズ画面のタイトルに戻るロゴ
		/** リザルト画面 */
		/** ゲームオーバー画面 */
	};
	virtual Type GetType() = 0;

	ActorBase2d( ApplicationBase& game,ModeBase& mode );
	virtual ~ActorBase2d();

	virtual void	Init();/*初期化*/
	virtual bool	Update();//
	virtual void	UpdateCollision();
	virtual bool	Draw();
	virtual void	DrawCollision();

	virtual AABB& GetCollision()
	{
		return _collision;
	}

	virtual Vector2& GetPosition()
	{
		return _pos;
	}
	virtual void	SetPosition( Vector2 pos )
	{
		_pos = pos;
	}
	virtual Vector2& GetSize()
	{
		return _size;
	}
	virtual void	SetSize( Vector2 size )
	{
		_size = size;
	}
	virtual bool	IsHitObject( ActorBase2d& object );	// 指定のオブジェクトと当たっているか？
protected:
	Vector2	_pos;		// 座標
	Vector2 _size;		// 大きさ
	float	_spd;		// 移動速度
	AABB	_collision;	// 当たり判定用矩形
	Vector2	_colPos,_colSize;	// 当たり判定位置サイズ(_posからの差分)
	EasingMode _easing = nullptr;
	int		_cnt;		// 動作カウンタ
};
