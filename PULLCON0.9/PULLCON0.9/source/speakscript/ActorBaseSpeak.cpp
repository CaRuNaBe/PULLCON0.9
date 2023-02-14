#include "ActorBaseSpeak.h"
ActorBaseSpeak::ActorBaseSpeak( ApplicationBase& game,int layer,ModeSpeakScript& mode )
	:GameBase( game,layer )
	,mode_speak_script( mode )
{
	Initialize();
}

ActorBaseSpeak::~ActorBaseSpeak()
{
}

void ActorBaseSpeak::Initialize()
{
	// î•ñ‚Ì‰Šú‰»
	_pos = {0,0};
	_cnt = 0;
}

bool ActorBaseSpeak::Update()
{
	_cnt++;
	return true;
}

bool ActorBaseSpeak::Draw()
{
	return true;
}

bool ActorBaseSpeak::DebugDraw()
{
	return true;
};