#include "EffectBase.h"
#include "../ApplicationGlobal.h"

EffectBase::EffectBase( ApplicationBase& game,ModeMainGame& mode )
	:base( game,mode )
{


	Init();
}

EffectBase::~EffectBase()
{

}

void EffectBase::Init()
{
	base::Init();

	_animeNo = 0;
	_animeCnt = 0;

}

bool EffectBase::Update()
{
	base::Update();
	return true;
}

bool EffectBase::Draw()
{
	base::Draw();
	return true;
}
