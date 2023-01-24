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

public:
	vector4 _vCursor;

	bool _blackout;
	bool _transparence;
	bool _clear;
protected:
	ApplicationBase& _game;


	int _cg;
	int _handlefont;


}; 


