#include "StageObject.h"
StageObject::StageObject( ApplicationBase& game,ModeBase& mode, int objectid,int collision )
	:base( game,mode )
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

bool StageObject::Update(  )
{
	base::Update( );



	return true;
}

bool StageObject::Draw(  )
{
	base::Draw(  );
	MV1DrawModel( _handle );
	return true;
}
