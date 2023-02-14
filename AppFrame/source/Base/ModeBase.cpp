

#include "ModeBase.h"

ModeBase::ModeBase( ApplicationBase& game,int layer )
	: GameBase( game,layer )
{
	Initialize();
}

ModeBase::~ModeBase()
{
}

bool ModeBase::Initialize()
{
	return true;
};
// çXêV
bool ModeBase::Update()
{
	return true;
}

// ï`âÊ
bool ModeBase::Draw()
{
	return true;
}

bool ModeBase::DebugDraw()
{
	return true;
};