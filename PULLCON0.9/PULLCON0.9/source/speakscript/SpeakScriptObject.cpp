#include "SpeakScriptObject.h"
namespace
{
	const std::string DELIMITER = ",";
}
SpeakScriptObject::SpeakScriptObject
( ApplicationBase& game,int layer,ModeSpeakScript& mode,int image_id,int music_id )
	: ActorSpeak( game,layer,mode )
{
	Initialize();
	{
		auto file_data = std::make_unique<ScriptsData>();
		const std::string FILEPASS = "res/script/gamescript/ImageId.json";
		const std::string ARRYNAME = "imageid";
		file_data->LoadJson( FILEPASS,ARRYNAME );

		auto image_pass_vector = string::Split( file_data->GetScriptLine( image_id ),DELIMITER );
		for ( int i = 0; i < image_pass_vector.size(); i++ )
		{
			int cg = ResourceServer::LoadGraph( image_pass_vector[i] );
			cg_ui.push_back( cg );
		}
	}
	{
		auto file_data = std::make_unique<ScriptsData>();
		const std::string FILEPASS = "res/script/gamescript/MusicId.json";
		const std::string ARRYNAME = "musicid";
		file_data->LoadJson( FILEPASS,ARRYNAME );

		music_hundle = ResourceServer::LoadSoundMem( file_data->GetScriptLine( music_id ).c_str() );
		PlaySoundMem( music_hundle,DX_PLAYTYPE_BACK,TRUE );
	}
}

SpeakScriptObject::~SpeakScriptObject()
{
}

void SpeakScriptObject::Initialize()
{
	ActorSpeak::Initialize();
	_pos = {0,0};
	_cnt = 0;
}

bool SpeakScriptObject::Update()
{
	ActorSpeak::Update();
	if ( !CheckSoundMem( music_hundle ) || music_hundle == -1 )
	{
		_cnt = 0;
		is_update_skip = true;
	}
	return true;
}


bool SpeakScriptObject::Draw()
{
	ActorSpeak::Draw();
	DrawTurnGraph( _pos.IntX(),_pos.IntY(),cg_ui[(_cnt / 10) % cg_ui.size()],TRUE );
	return true;
}

bool SpeakScriptObject::DebugDraw()
{
	ActorSpeak::DebugDraw();
	return true;
};