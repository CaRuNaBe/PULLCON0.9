/*
** ObjectBase
*/

#include "DxLib.h"
#include "ObjectBase.h"

ObjectBase::ObjectBase()
	:isUpdateSkip(false)
	,isDrawSkip(false)
{
	Init();
}

ObjectBase::~ObjectBase()
{}

void ObjectBase::Init()
{
	// 情報の初期化
	_dead = false;
}

void ObjectBase::Update(ApplicationBase& game)
{}

void ObjectBase::Draw(ApplicationBase& game)
{}

