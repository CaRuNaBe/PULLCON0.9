#pragma once
#include "appframe.h"

class StageObject:
    public ActorBase3D
{
	using base = ActorBase3D;
public:
	StageObject( ApplicationBase& game,ModeBase& mode,int objectid,int collision ,int pieces_coll);
	virtual ~StageObject();
	virtual Type GetType()
	{
		return Type::kStageObject;
	}
	// �X�e�[�W�I�u�W�F�N�g�̏��
	enum class State {
		NUM, //�������
		STATE,//�v���C�A�u�����
	};

	virtual void Init();
	virtual bool Update(  );
	virtual bool Draw( );

	void AddCollision();

protected:
	State  _stateStageObject;

	int    _iPiecesColl;
	int    _handle;
};

