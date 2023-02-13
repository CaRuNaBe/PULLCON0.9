#pragma once
#include "appframe.h"
class EnemyColumn :
    public ActorBase3D
{
	using base = ActorBase3D;
public:
	EnemyColumn(ApplicationBase& game, ModeBase& mode);
	virtual ~EnemyColumn();
	virtual Type GetType()
	{
		return Type::kEnemySkyhunter;
	}
	// �X�J�C�n���^�[����̏��
	enum class State
	{
		WAIT,//�ҋ@���
		PLAY,//����
	};
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage(ModeBase& mode);
	void SetVelocity();   // ���x�x�N�g��
	void AddPieces();

protected:
	State   _stateEnemyColumn;

};

