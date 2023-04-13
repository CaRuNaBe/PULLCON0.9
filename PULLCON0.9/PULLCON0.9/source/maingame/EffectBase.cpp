#include "EffectBase.h"
#include "../ApplicationGlobal.h"

EffectBase::EffectBase(ApplicationBase& game, int layer, ModeMainGame& mode)
	:ActorMainGame(game, layer, mode)
{
	Initialize();
}

EffectBase::~EffectBase()
{}

void EffectBase::Initialize()
{
	ActorMainGame::Initialize();
	_animeNo = 0;
	_animeCnt = 0;
}

bool EffectBase::Update()
{
	ActorMainGame::Update();
	return true;
}

bool EffectBase::Draw()
{
	ActorMainGame::Draw();
	return true;
}
