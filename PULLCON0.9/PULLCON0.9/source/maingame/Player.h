#pragma once
#include "appframe.h"

// �J����
class Camera
{
public:
	vector4	_vPos;					// �ʒu
	vector4	_vPosEvent;			// �����������J�����ʒu
	vector4	_vTarget;				// �����_
	vector4	_vMemory;				// �x�N�g���ۑ��p
	float	_clipNear,_clipFar;	// �N���b�v
};

class Player: public ActorBase3D
{
	typedef ActorBase3D base;
public:
	Player( ApplicationBase& game,ModeBase& mode );
	virtual ~Player();
	virtual Type GetType()
	{
		return Type::kPlayer;
	}
// �v���C���[�̏��
	enum class State
	{
		NUM, //�������
		PLAY,//�v���C�A�u�����
		EVENT//�C�x���g���
	};

	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	void CameraUpdate();    // �J�����X�V
	void EventCamera();    // �J����
	void AddBullet( vector4 pos );
	State GetPlayerState()
	{
		return _statePlayer;
	}
	int GetPush()
	{
		return _push;
	}
protected:
	// �J����
	Camera	_cam;

	State  _statePlayer;      // �v���C���[�X�e�[�^�X

	vector4 _vMoevDir;
	int    _push;             // �{�^���A�ŉ�
	bool   _isHit;            // ����������
	bool   _isHitObject;      // �I�u�W�N�g�Ɠ���������
	float  _fSpeedIint;       // �v���C���[�̑��x�̏����l
	float  _fRotateAirscrew;  // �v���y���̉�]
	float  _fAxialX;
	float  _fAxialZ;

	int    _handleBody;
	int    _handleAirscrew;
	int    _handleMagnet;
	int    _handleBackAirscrew;
	int    _handlefont;
	int    _se;
	int    _seBullet;

};
