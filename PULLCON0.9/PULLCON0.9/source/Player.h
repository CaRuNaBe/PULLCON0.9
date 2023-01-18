#pragma once
#include "appframe.h"

// �J����
class Camera {
public:
	vector4	_vPos;					// �ʒu
	vector4	_vTarget;				// ����
	float	_clipNear, _clipFar;	// �N���b�v
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

	void CameraUpdate(ApplicationBase& game);    // �J�����X�V
	void EventCamera(ApplicationBase& game);    // �J����
	void AddBullet(ModeBase& mode);

protected:
	// �J����
	Camera	_cam;

	float  _speed;
	float  _rotatX;
	float  _rotatY;
	int    _push;

	int    _handle;
	int    _cg;

};
