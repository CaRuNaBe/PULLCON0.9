#pragma once
#include "appframe.h"
#include "EnemyColumn.h"
class EnemySkyhunter :
	public ActorBase3D
{
	using base = ActorBase3D;
public:
	EnemySkyhunter(ApplicationBase& game, ModeBase& mode, EnemyColumn& skyhunter);
	virtual ~EnemySkyhunter();
	virtual Type GetType()
	{
		return Type::kEnemySkyhunter;
	}
	// �X�J�C�n���^�[�̏��
	enum class State
	{
		NUM, //�������
		WAIT,//�ҋ@���
		PLAY,//�}���̐�
	};
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void AddBullet();

protected:
	EnemyColumn& _column;

	State   _stateEnemySkyhunter;

	int    _handle;
};