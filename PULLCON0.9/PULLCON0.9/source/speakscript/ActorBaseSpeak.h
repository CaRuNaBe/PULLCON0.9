#pragma once
#include "appframe.h"
class ModeSpeakScript;
class ActorBaseSpeak:public GameBase
{
public:
	ActorBaseSpeak( ApplicationBase& game,int layer,ModeSpeakScript& mode );
	virtual ~ActorBaseSpeak();

	virtual void Initialize();/*初期化*/
	virtual bool Update();//
	virtual bool Draw();
	virtual bool DebugDraw();
	virtual void SetPosi( math::Vector2 _pos )
	{
		this->_pos = _pos;
	}

protected:
	ModeSpeakScript& mode_speak_script;
	math::Vector2 _pos; // 座標
	int _cnt; // 動作カウンタ
};

