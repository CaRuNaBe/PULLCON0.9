#include "StageObject.h"
StageObject::StageObject( ApplicationBase& game,ModeBase& mode,int objectid,int collision )
	:base( game,mode )
{
	Init();
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

	_handle = ResourceServer::LoadMV1Model( file_pass_data->GetScriptLine( objectid ).c_str() );
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
	_collision._fRadius = _fRadius * _fScale;
	UpdateCollision();
	return true;
}

bool StageObject::Draw()
{
	base::Draw();
	// モデル拡大
	MV1SetScale( _handle,VGet( _fScale,_fScale,_fScale ) );

	MV1SetPosition( _handle,math::ToDX( _vPos ) );
	// コリジョン描画
	vector4 color = {255, 0, 255};
	SetUseLighting( FALSE );
		// モデル描画
	MV1DrawModel( _handle );
	MV1SetPosition( _handle,math::ToDX(_vPos) );
	DrawCollisionObject( color );
	return true;
}
