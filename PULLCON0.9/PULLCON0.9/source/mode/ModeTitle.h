#pragma once
#include<memory>
#include "appframe.h"
class ActorTitle;
class ModeTitle:public GameBase
{
public:
	ModeTitle( ApplicationBase& game,int layer );
	virtual ~ModeTitle();
	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();
	virtual bool DebugDraw();
	GameServer2<ActorTitle>& Get2DobjectServer()
	{
		return object_out_game;
	}
private:
	enum class State
	{
		BASE,
		CREDIT
	};
	using SwitchFunctionTitle = std::map<ModeTitle::State,bool(ModeTitle::*)()>;
	State title_state;
	GameServer2<ActorTitle> object_out_game;
};