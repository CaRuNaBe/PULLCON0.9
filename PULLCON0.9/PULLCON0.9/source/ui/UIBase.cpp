#include "UIBase.h"
UIBase::UIBase( ApplicationBase& game,int layer,ModeBase& _base )
	:GameBase( game,layer )
	,mode_base( _base )
{
}

UIBase::~UIBase()
{
};

bool UIBase::Initialize()
{
	return true;
};

bool UIBase::Update()
{
	return true;
};

bool UIBase::Draw()
{
	return true;
};

bool UIBase::DebugDraw()
{
	return true;
};
