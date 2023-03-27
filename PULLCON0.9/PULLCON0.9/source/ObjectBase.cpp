/*
** ObjectBase
*/

#include "DxLib.h"
#include "ObjectBase.h"
ObjectBase::ObjectBase( ApplicationBase& game )
	:isUpdateSkip( false )
	,isDrawSkip( false )
	,_game( game )
{
	Init();
}

ObjectBase::~ObjectBase()
{
}

void ObjectBase::Init()
{
	// 情報の初期化
	_dead = false;
}

bool ObjectBase::Update()
{
	return true;
}

bool ObjectBase::Draw()
{
	
	return true;
}

