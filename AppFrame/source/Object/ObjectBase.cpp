/*
** ObjectBase
*/

#include "DxLib.h"
#include "ObjectBase.h"
#include "../Mode/ModeBase.h"
ObjectBase::ObjectBase( ApplicationBase& game ,ModeBase& mode )
	:isUpdateSkip(false)
	,isDrawSkip(false)
	, _game( game )
, _mode( mode )
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

bool ObjectBase::Update()
{
	return true;
}

bool ObjectBase::Draw()
{
	return true;
}

