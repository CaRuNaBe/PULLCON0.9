#include "ModeSclipt.h"
#include "../Application/ApplicationBase.h"

ModeSclipt::ModeSclipt(ApplicationBase& game,int layer,std::string storyname)
	: ModeBase(game,layer)
	,script(storyname,game)
{}

ModeSclipt::~ModeSclipt()
{}

// 更新
bool ModeSclipt::Update()
{
	ModeBase::Update();
	script.Update(_game);
	if(_game.GetScliptFlagManager()->GetisEndsclipt())
	{
		_game.GetScliptFlagManager()->SetisEndsclipt(false); 
		_game.GetScliptFlagManager()->SetisLoadend(false); 
		_game.GetScliptFlagManager()->SetisBlackbackground(false); 
		//スクリプトが終わったので自分自身を消去
		_game.GetModeServer()->Del(*this);
	}
	return true;
}

// 描画
bool ModeSclipt::Draw()
{
	ModeBase::Draw();
	script.Draw(_game);
	return true;
};