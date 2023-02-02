#include "StageObject.h"
StageObject::StageObject( ApplicationBase& game,ModeBase& mode, int objectid,int collision )
	:base( game,mode )
{
	if ( collision == 1 )
	{
		_coll = true;
	}
	else
	{
		_coll = false;
	}
	/*
	switch ( objectid )
	{

		default:
			break;
	}
	*/
	Init();
}

StageObject::~StageObject()
{

}

void StageObject::Init()
{
	base::Init();

}

bool StageObject::Update(  )
{
	base::Update( );

	_collision._fRadius = _collision._fRadius * _fScale;
	UpdateCollision();

	return true;
}

bool StageObject::Draw(  )
{
	base::Draw(  );
	// ƒ‚ƒfƒ‹Šg‘å
	MV1SetScale(_handle, VGet(_fScale, _fScale, _fScale));
	// ƒ‚ƒfƒ‹•`‰æ
	MV1DrawModel( _handle );

	// ƒRƒŠƒWƒ‡ƒ“•`‰æ
	vector4 color = { 255, 255, 255 };
	if (!_coll) {
		DrawCollision(color);
	}
	return true;
}
