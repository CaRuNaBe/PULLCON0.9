#pragma once
#include "appframe.h"
#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
class EnemyKobae :
	public ActorBase3D {
	using base = ActorBase3D;
public:
	EnemyKobae(ApplicationBase& game, ModeMainGame& mode);
	virtual ~EnemyKobae();
	virtual Type GetType() { return Type::kEnemySkyhunter; }
	// �R�o�G�̏��
	enum class State {
		WAIT,//�ҋ@���
		PLAY,//�}���̐�
	};
	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void SetVelocity();   // ���x�x�N�g��
	void AddBullet();

protected:
	State   _stateEnemyKobae;

	int    _handle;
	int    _handleStage;
};

