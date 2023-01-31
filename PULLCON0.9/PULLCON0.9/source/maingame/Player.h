#pragma once
#include "appframe.h"

// カメラ
class Camera {
public:
	vector4	_vPos;					// 位置
	vector4	_vTarget;				// 注視点
	vector4	_vMemory;				// ベクトル保存用
	float	_clipNear, _clipFar;	// クリップ
};

class Player : public ActorBase3D {
	typedef ActorBase3D base;
public:
	Player( ApplicationBase& game,ModeBase& mode );
	virtual ~Player();
	virtual Type GetType() { return Type::kPlayer; }
	// プレイヤーの状態
	enum class State
	{
		NUM, //初期状態
		PLAY,//プレイアブル状態
		EVENT//イベント状態
	};

	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	void CameraUpdate();    // カメラ更新
	void EventCamera();    // カメラ
	void AddBullet();

protected:
	// カメラ
	Camera	_cam;

	State  _statePlayer;

	int    _push;

	int    _handle;
	int    _cg;

};
