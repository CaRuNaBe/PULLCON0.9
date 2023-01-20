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
	Player();
	virtual ~Player();
	virtual Type GetType() { return Type::kPlayer; }
	// プレイヤーの状態
	enum class State
	{
		PLAY,//プレイアブル状態
		EVENT//イベント状態
	};

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);

	void CameraUpdate(ApplicationBase& game);    // カメラ更新
	void EventCamera(ApplicationBase& game);    // カメラ
	void AddBullet(ModeBase& mode);

protected:
	// カメラ
	Camera	_cam;

	State  _statePlayer;

	int    _push;

	int    _handle;
	int    _cg;

};
