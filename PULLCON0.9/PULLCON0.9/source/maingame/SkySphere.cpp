#include "SkySphere.h"
namespace
{
	const auto SUNNY = 1;
	const auto CLOUDY = 2;
}
SkySphere::SkySphere( ApplicationBase& game,ModeBase& mode,int objectid )
	:base( game,mode )
{
	switch ( objectid )
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

bool SkySphere::Update()
{
	base::Update();



	return true;
}

bool SkySphere::Draw()
{
	base::Draw();
	MV1SetScale( _handle,VGet( 35.0f,35.0f,35.0f ) );
	SetUseLighting( FALSE );
	MV1DrawModel( _handle );
	SetUseLighting( TRUE );
	return true;
}
