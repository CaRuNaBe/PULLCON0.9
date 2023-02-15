#include "SkySphere.h"

SkySphere::SkySphere( ApplicationBase& game,ModeBase& mode,int objectid )
	:base( game,mode )
{
	auto file_pass_data = std::make_unique<ScriptsData>();
	const std::string FILEPASS = "res/script/gamescript/ObjectId.json";
	const std::string ARRYNAME = "ObjectId";
	file_pass_data->LoadJson( FILEPASS,ARRYNAME );

	_handle = ResourceServer::LoadMV1Model( file_pass_data->GetScriptLine( objectid ).c_str() );



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
	MV1SetScale( _handle,VGet( 10.0f,10.0f,10.0f ) );
	SetUseLighting( FALSE );
	MV1DrawModel( _handle );
	SetUseLighting( TRUE );
	return true;
}
