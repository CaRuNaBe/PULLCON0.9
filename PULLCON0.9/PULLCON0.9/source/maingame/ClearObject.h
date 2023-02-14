#pragma once
#include "appframe.h"
class ClearObject:
	public ActorBase3D
{
	using base = ActorBase3D;
public:
	ClearObject( ApplicationBase& game,ModeBase& mode,float _radius );
	virtual ~ClearObject();
	virtual Type GetType()
	{
		return Type::kClearObject;
	}
	// �v���C���[�̏��
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
	State   _stateClearObject;  // �K���V�b�v�X�e�[�^�X

	vector4 _vObjective;  // �~�O�����S���W

	int    _handle;
	float radius;
};

