#pragma once
#include "appframe.h"
using namespace math;

// �J����
class Camera {
public:
	VECTOR	_vPos;					// �ʒu
	VECTOR	_vTarget;				// ����
	float	_clipNear, _clipFar;	// �N���b�v
};

class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	ModeGame(ApplicationBase& game,int layer);
	virtual ~ModeGame();
	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();

protected:

	vector4 _vCursor;

	int _handleSkySphere;
	int _cg;


}; 


