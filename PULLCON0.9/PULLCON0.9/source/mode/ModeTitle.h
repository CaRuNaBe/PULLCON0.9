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
	GameServerShared<ActorTitle>& Get2DobjectServer()
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
	GameServerShared<ActorTitle> object_out_game;
};