#include "SpeakScriptObject.h"
#include "../ApplicationGlobal.h"
namespace
{
	const std::string DELIMITER = ",";
}
SpeakScriptObject::SpeakScriptObject
( ApplicationBase& game,int layer,ModeSpeakScript& mode,int image_id,int music_id )
	: ActorSpeak( game,layer,mode )
{
	Initialize();


	auto image_pass_vector = string::Split( gGlobal.image_pass_date->GetScriptLine( image_id ),DELIMITER );
	for ( int i = 0; i < image_pass_vector.size(); i++ )
	{
		int cg = ResourceServer::LoadGraph( image_pass_vector[i] );
		cg_ui.push_back( cg );
	}


	music_hundle = ResourceServer::LoadSoundMem( gGlobal.music_pass_date->GetScriptLine( music_id ).c_str() );
	PlaySoundMem( music_hundle,DX_PLAYTYPE_BACK,TRUE );

}

SpeakScriptObject::~SpeakScriptObject()
{
	StopSoundMem( music_hundle );
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
	DrawGraph( _pos.IntX(),_pos.IntY(),cg_ui[(_cnt / 10) % cg_ui.size()],TRUE );
	return true;
}

bool SpeakScriptObject::DebugDraw()
{
	ActorSpeak::DebugDraw();
	return true;
};