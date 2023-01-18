#pragma once
#include "appframe.h"

// カメラ
class Camera {
public:
	vector4	_vPos;					// 位置
	vector4	_vTarget;				// 距離
	float	_clipNear, _clipFar;	// クリップ
};

class Player : public ActorBase3D {
	typedef ActorBase3D base;
public:
	Player();
	virtual ~Player();
	virtual Type GetType() { return Type::kPlayer; }

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);

	void CameraUpdate(ApplicationBase& game);    // カメラ更新
	void EventCamera(ApplicationBase& game);    // カメラ
	void AddBullet(ModeBase& mode);

protected:
	// カメラ
	Camera	_cam;

	float  _speed;
	float  _rotatX;
	float  _rotatY;
	int    _push;

	int    _handle;
	int    _cg;

};
