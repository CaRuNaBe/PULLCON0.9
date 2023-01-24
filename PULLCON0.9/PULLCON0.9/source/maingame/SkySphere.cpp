#include "SkySphere.h"
SkySphere::SkySphere()
	:base()
{
	_handle = MV1LoadModel( "res/stage/skysphere/mv1/cg_stageSkymap_1.mv1" );

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

	MV1DrawModel( _handle );
	return true;
}
