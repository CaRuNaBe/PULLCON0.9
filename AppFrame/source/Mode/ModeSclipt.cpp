#include "ModeSclipt.h"
#include "../Application/ApplicationBase.h"

ModeSclipt::ModeSclipt(ApplicationBase& game,int layer,std::string storyname)
	: ModeBase(game,layer)
	,script(storyname,game)
{}

ModeSclipt::~ModeSclipt()
{}

// �X�V
bool ModeSclipt::Update()
{
	ModeBase::Update();
	script.Update(_game);
	if(_game.GetScliptFlagManager()->GetisEndsclipt())
	{
		_game.GetScliptFlagManager()->SetisEndsclipt(false); 
		_game.GetScliptFlagManager()->SetisLoadend(false); 
		_game.GetScliptFlagManager()->SetisBlackbackground(false); 
		//�X�N���v�g���I������̂Ŏ������g������
		_game.GetModeServer()->Del(*this);
	}
	return true;
}

// �`��
bool ModeSclipt::Draw()
{
	ModeBase::Draw();
	script.Draw(_game);
	return true;
};