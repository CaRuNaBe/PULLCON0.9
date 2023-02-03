#include "StageObject.h"
StageObject::StageObject( ApplicationBase& game,ModeBase& mode,int objectid,int collision )
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
	auto file_pass_data = std::make_unique<ScriptsData>();
	const std::string FILEPASS = "res/script/gamescript/ObjectId.json";
	const std::string ARRYNAME = "ObjectId";
	file_pass_data->LoadJson( FILEPASS,ARRYNAME );

	_handle = MV1LoadModel( file_pass_data->GetScriptLine( objectid ).c_str() );


	Init();
}

StageObject::~StageObject()
{

}

void StageObject::Init()
{
	base::Init();

}

bool StageObject::Update()
{
	base::Update();

	_collision._fRadius = _collision._fRadius * _fScale;
	UpdateCollision();

	return true;
}

bool StageObject::Draw()
{
	base::Draw();
	// ƒ‚ƒfƒ‹Šg‘å
	MV1SetScale( _handle,VGet( _fScale,_fScale,_fScale ) );
	// ƒ‚ƒfƒ‹•`‰æ
	MV1DrawModel( _handle );
	MV1SetPosition( _handle,math::ToDX(_vPos) );
	// ƒRƒŠƒWƒ‡ƒ“•`‰æ
	vector4 color = {255, 255, 255};
	if ( !_coll )
	{
		DrawCollision( color );
	}
	return true;
}
