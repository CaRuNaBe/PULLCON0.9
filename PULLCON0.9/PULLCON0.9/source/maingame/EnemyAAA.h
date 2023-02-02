#pragma once
#include "appframe.h"


class EnemyAAA: public ActorBase3D
{
	typedef ActorBase3D base;
public:
	EnemyAAA( ApplicationBase& game,ModeBase& mode,int min_id,int max_id,int pile_num, vector4 _vPosi);
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

	virtual void Init(int pile_num, vector4 _vPosi);
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void AddBullet();
	void AddPieces(int pile_num);

	void SetAxialX(float _x_rad) { _fAxialX = _x_rad; }
	void SetAxialY(float _y_rad) { _fAxialY = _y_rad; }
	void SetType(int _aim_player) { _iType = _aim_player; }
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
