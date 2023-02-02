#pragma once
#include "appframe.h"


class EnemyAAA: public ActorBase3D
{
	typedef ActorBase3D base;
public:
	EnemyAAA( ApplicationBase& game,ModeBase& mode,int min_id,int max_id,int pile_num );
	virtual ~EnemyAAA();
	virtual Type GetType()
	{
		return Type::kEnemyAAA;
	}
// �΋�C�̏��
	enum class State
	{
		NUM,//�n���̑΋�C
		PLAY,//�v���C�A�u�����
		EVENT,//�C�x���g���
		WEAPON//���퉻
	};

	virtual void Init(int pile_num);
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void AddBullet();
	void AddPieces(int pile_num);

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
