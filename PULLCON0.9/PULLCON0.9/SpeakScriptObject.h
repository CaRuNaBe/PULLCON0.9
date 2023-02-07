#pragma once
#include "appframe.h"
class SpeakScriptObject:
    public ActorBaseSpeak
{
	using ActorSpeak = ActorBaseSpeak;
public:
	SpeakScriptObject( ApplicationBase& game,ModeBase& mode );
	~SpeakScriptObject();

	void	Init();//‰Šú‰»
	bool	Update();
	bool	Draw();
private:
};

