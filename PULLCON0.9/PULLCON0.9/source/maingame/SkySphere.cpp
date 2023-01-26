#include "SkySphere.h"
namespace
{
	const auto SUNNY = 1;
	const auto CLOUDY = 2;
}
SkySphere::SkySphere( int object_id )
	:base()
{
	switch ( object_id )
	{
		case SUNNY:
			_handle = MV1LoadModel( "res/stage/skysphere/mv1/cg_stageSkymap_1.mv1" );
			break;
		case CLOUDY:
			_handle = MV1LoadModel( "res/stage/skysphere/mv1/cg_stageSkymap_1.mv1" );
			break;
		default:
			break;
	}


	Init();
}

SkySphere::~SkySphere()
{

}

void SkySphere::Init()
{
	base::Init();


}

bool SkySphere::Update( ApplicationBase& game,ModeBase& mode )
{
	base::Update( game,mode );



	return true;
}

bool SkySphere::Draw( ApplicationBase& game,ModeBase& mode )
{
	base::Draw( game,mode );
	MV1SetScale( _handle,VGet( 35.0f,35.0f,35.0f ) );
	SetUseLighting(FALSE);
	MV1DrawModel(_handle);
	SetUseLighting(TRUE);
	return true;
}
