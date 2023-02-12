/*
** ModeBase
*/

#include "ModeBase.h"

ModeBase::ModeBase(ApplicationBase& game, int layer)
	: _game(game)
	,_dead(false)
	,_isModeSkip(false)
	,_isDrawSkip(false)
	,_layer(layer)
{
	Initialize();
}

ModeBase::~ModeBase()
{}

bool ModeBase::Initialize()
{
	return true;
};
// �X�V
bool ModeBase::Update()
{
	return true;
}

// �`��
bool ModeBase::Draw()
{
	return true;
}
