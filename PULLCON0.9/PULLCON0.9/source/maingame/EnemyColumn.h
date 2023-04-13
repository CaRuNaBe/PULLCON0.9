#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
class EnemyColumn :public ActorMainGame
{
public:
	EnemyColumn(ApplicationBase& game, int layer, ModeMainGame& mode, vector4 pos);
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
	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void SetVelocity();   // ���x�x�N�g��
	void AddPieces(vector4 pos);

protected:
	State   _stateEnemyColumn;

	int    _handleStage;
};

