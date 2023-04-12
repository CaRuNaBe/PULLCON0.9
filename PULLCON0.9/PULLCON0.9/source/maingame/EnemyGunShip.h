#pragma once
#include "appframe.h"
#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
class EnemyGunShip :
	public ActorBase3D {
	using base = ActorBase3D;
public:
	EnemyGunShip(ApplicationBase& game, ModeMainGame& mode, float _radius);
	virtual ~EnemyGunShip();
	virtual Type GetType() { return Type::kClearObject; }
	// �K���V�b�v�̏��
	enum class State {
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
	State   _stateClearObject;

	vector4 _vObjective;  // �~�O�����S���W

	int    _handle;
	float radius;
};

