#include "StageObject.h"
StageObject::StageObject( int stageid,int collision )
	:base()
{
	if ( collision == 0 )
	{
	}
	switch ( stageid )
	{
		case STAGE_1:
			_handle = MV1LoadModel( "res/stage/stage_file_1/mv1/stage1/cg_stage1.mv1" );
			break;

			break;
		default:
			break;
	}

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
