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
	// î•ñ‚Ì‰Šú‰»
	_dead = false;
}

bool ObjectBase::Update(ApplicationBase& game)
{
	return true;
}

bool ObjectBase::Draw(ApplicationBase& game)
{
	return true;
}

