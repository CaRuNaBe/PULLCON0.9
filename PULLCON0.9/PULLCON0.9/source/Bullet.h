#pragma once
#include "appframe.h"

class Bullet : public ActorBase3D{
	typedef ActorBase3D base;
public:
	Bullet();
	virtual ~Bullet();
	virtual Type GetType() { return Type::kBullet; }

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);

	virtual void Damage(ModeBase& mode);

protected:

	float  _speed;
	int    _handle;
	
	int _grHandle;  // ���݂̃O���t�B�b�N�n���h��
	std::vector<int>_grAllHandles;// �S�ẴO���t�B�b�N�n���h��
	int _animeNo;// �A�j���ԍ�
	int _animeMax;// �A�j���ő吔
};

