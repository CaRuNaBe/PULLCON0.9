#pragma once
#include "appframe.h"

// �J����
class Camera {
public:
	vector4	_vPos;					// �ʒu
	vector4	_vPosEvent;			// �����������J�����ʒu
	vector4	_vTarget;				// �����_
	vector4	_vMemory;				// �x�N�g���ۑ��p
	float	_clipNear, _clipFar;	// �N���b�v
};

class Player : public ActorBase3D {
	typedef ActorBase3D base;
public:
	Player();
	virtual ~Player();
	virtual Type GetType() { return Type::kPlayer; }
	// �v���C���[�̏��
	enum class State
	{
		NUM, //�������
		PLAY,//�v���C�A�u�����
		EVENT//�C�x���g���
	};

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);

	void CameraUpdate(ApplicationBase& game);    // �J�����X�V
	void EventCamera(ApplicationBase& game);    // �J����
	void AddBullet(ModeBase& mode);

protected:
	// �J����
	Camera	_cam;

	State  _statePlayer;  // �v���C���[�X�e�[�^�X

	int    _push;   // �{�^���A�ŉ�
	bool   _isHit;  // ����������

	int    _handle;
	int    _handlefont;
	int    _se;
	int    _seBullet;

};
