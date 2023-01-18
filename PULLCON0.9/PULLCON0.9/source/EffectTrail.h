#pragma once
#include "appframe.h"

class EffectTrail : public ActorBase3D
{
	typedef ActorBase3D base;
public:
	EffectTrail();
	virtual ~EffectTrail();
	virtual Type GetType() { return Type::kEffect; }

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);

protected:

	int _grHandle;  // ���݂̃O���t�B�b�N�n���h��
	std::vector<int>_grAllHandles;// �S�ẴO���t�B�b�N�n���h��
	int _animeNo;// �A�j���ԍ�
	int _animeMax;// �A�j���ő吔
	int _animeCnt;// �A�j���J�E���g
};

