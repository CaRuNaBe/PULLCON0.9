#pragma once
#include "appframe.h"
#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
class EnemyColumn :
	public ActorBase3D {
	using base = ActorBase3D;
public:
	EnemyColumn(ApplicationBase& game,ModeMainGame& mode, vector4 pos);
	virtual ~EnemyColumn();
	virtual Type GetType() { return Type::kEnemySkyhunter; }
	// �X�J�C�n���^�[����̏��
	enum class State {
		WAIT,//�ҋ@���
		PLAY,//����
	};
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void SetVelocity();   // ���x�x�N�g��
	void AddPieces(vector4 pos);

protected:
	State   _stateEnemyColumn;

};

