#include "StageObject.h"
StageObject::StageObject( int objectid,int collision )
	:base()
{
	if ( collision == 1 )
	{
		is_coll = true;
	}
	else
	{
		is_coll = false;
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

bool StageObject::Update( ApplicationBase& game,ModeBase& mode )
{
	base::Update( game,mode );



	return true;
}

bool StageObject::Draw( ApplicationBase& game,ModeBase& mode )
{
	base::Draw( game,mode );
	MV1DrawModel( _handle );
	return true;
}
