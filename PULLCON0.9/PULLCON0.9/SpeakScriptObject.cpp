#include "SpeakScriptObject.h"
SpeakScriptObject::SpeakScriptObject( ApplicationBase& game,ModeBase& mode ): ActorSpeak( game,mode )
{
	Init();
}

SpeakScriptObject::~SpeakScriptObject()
{    // �쐬�����t�H���g�f�[�^���폜����
}

void SpeakScriptObject::Init()
{
	ActorSpeak::Init();
	_pos = {0,0};
	_cnt = 0;
}

bool SpeakScriptObject::Update()
{
	ActorSpeak::Update();
	return true;
}


bool SpeakScriptObject::Draw()
{
	ActorSpeak::Draw();
	return true;
}