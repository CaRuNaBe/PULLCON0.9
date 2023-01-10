#pragma once
#include "appframe.h"
using namespace math;

class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	ModeGame(ApplicationBase& game,int layer);
	virtual ~ModeGame();
	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();

	void SetCursor(const vector4& pos) { _vCursor = pos; }

protected:

	vector4 _vCursor;

	int _handleSkySphere;
	int _cg;


}; 


