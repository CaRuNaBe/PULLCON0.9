#include "ModeSclipt.h"

ModeSclipt::ModeSclipt(ApplicationBase& game,int layer,std::string storyname)
	: ModeBase(game,layer)
{}

ModeSclipt::~ModeSclipt()
{}

// �X�V
bool ModeSclipt::Update()
{
	ModeBase::Update();

	return true;
}

// �`��
bool ModeSclipt::Draw()
{
	ModeBase::Draw();
	return true;
};