#pragma once
#include "appframe.h"


class EnemyAAA : public ActorBase3D {
	typedef ActorBase3D base;
public:
	EnemyAAA();
	virtual ~EnemyAAA();
	virtual Type GetType() { return Type::kEnemyAAA; }
	// �΋�C�̏��
	enum class State
	{
		NUM,//�n���̑΋�C
		PLAY,//�v���C�A�u�����
		EVENT,//�C�x���g���
		WEAPON//���퉻
	};

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);

	virtual void Damage(ModeBase& mode);
	void AddBullet(ModeBase& mode);
	void AddPieces(ModeBase& mode);

protected:
	State   _stateAAA;

	int    _iType;  // �^�C�v 0,�ǔ��� 1,�Œ莮
	int    _iPossession;  // �΋�C�p�[�c�̏��L��
	int    _iPart;  // �n���̑΋�C�p�[�c�̔ԍ�
	float  _fAxialY;  // Y����](�x���@)	
	float  _fAxialX;  // X����](�x���@)
	bool   _have;  // �����Ă��邩

	int    _handle_body;
	int    _handle_turret;

};
