#include "BaseUI.h"
BaseUI::BaseUI( ApplicationBase& game,int layer,ModeBase& _base )
	:GameBase( game,layer )
	,mode_base( _base )
{
}

BaseUI::~BaseUI()
{
};

bool BaseUI::Initialize()
{
	return true;
};

bool BaseUI::Update()
{
	return true;
};

bool BaseUI::Draw()
{
	return true;
};

bool BaseUI::DebugDraw()
{
	return true;
};
