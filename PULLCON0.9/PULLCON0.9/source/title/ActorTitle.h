#pragma once
#include "appframe.h"
#include "../mode/ModeTitle.h"
#include "../mode/ModeTitle.h"
class ActorTitle:public GameBase
{
public:
	enum class Type
	{
		// 種別の列挙型
		/** タイトル画面 */
		KBASE,     // 0 アクター
		KPLAYER,     // 1 プレイヤー
		KTITLELOGO,     // 2 タイトルロゴ
		KGAMESTARTLOGO, // 3 ゲームスタートロゴ
		KGAMESTARTGUID,  // 4 ゲームスタートガイド
		KCREDITLOGO,   // 5 クレジットロゴ
		KCREDITGUID,     // 6 クレジットガイド
		KENDLOGO,     // 7 ゲーム終了ロゴ
		KENDGUID,        // 8 ゲーム終了ガイド
	};
	virtual Type GetType() = 0;

	ActorTitle( ApplicationBase& game,int layer,ModeTitle& mode );
	virtual ~ActorTitle();

	virtual void Initialize();/*初期化*/
	virtual bool Update();//
	virtual void UpdateCollision();
	virtual bool Draw();
	virtual void DrawCollision();
	virtual bool DebugDraw();
	virtual  math::AABB& GetCollision()
	{
		return _collision;
	}

	virtual  math::Vector2& GetPosition()
	{
		return _pos;
	}
	virtual void SetPosition( const math::Vector2& pos )
	{
		_pos = pos;
	}
	virtual  math::Vector2& GetSize()
	{
		return _size;
	}
	virtual void SetSize( math::Vector2& size )
	{
		_size = size;
	}
	virtual  bool  IsHitObject( ActorTitle& object );// 指定のオブジェクトと当たっているか？
protected:
	ModeTitle& _mode;
	math::Vector2 _pos;// 座標
	math::Vector2 _size; // 大きさ
	float _spd; // 移動速度
	math::AABB _collision; // 当たり判定用矩形
	math::Vector2	_colPos,_colSize;	// 当たり判定位置サイズ(_posからの差分)
	math::EasingMode _easing = nullptr;
	int		_cnt;		// 動作カウンタ
	const int low_movement_pull;
	const int up_movement_pull;
};
