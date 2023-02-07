#include "ActorBaseSpeak.h"
ActorBaseSpeak::ActorBaseSpeak( ApplicationBase& game,ModeBase& mode ):base( game,mode )
{
	Init();
}

ActorBaseSpeak::~ActorBaseSpeak()
{
}

void ActorBaseSpeak::Init()
{
	base::Init();
	// î•ñ‚Ì‰Šú‰»
	_pos = {0,0};
	_cnt = 0;
}

bool ActorBaseSpeak::Update()
{
	base::Update();
	_cnt++;
	return true;
}

bool ActorBaseSpeak::Draw()
{
	base::Draw();
	return true;
}
