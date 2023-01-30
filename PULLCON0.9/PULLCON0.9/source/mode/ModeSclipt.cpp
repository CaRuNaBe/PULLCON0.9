#include "ModeSclipt.h"

ModeSclipt::ModeSclipt(ApplicationBase& game,int layer,std::string storyname)
	: ModeBase(game,layer)
{}

ModeSclipt::~ModeSclipt()
{}

// çXêV
bool ModeSclipt::Update()
{
	ModeBase::Update();

	return true;
}

// ï`âÊ
bool ModeSclipt::Draw()
{
	ModeBase::Draw();
	return true;
};