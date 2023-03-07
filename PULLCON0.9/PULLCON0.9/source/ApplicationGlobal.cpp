
#include "appframe.h"
#include "ApplicationGlobal.h"

// À‘Ì
ApplicationGlobal		gGlobal;
namespace
{
	const std::string IMAGE_ID_FILEPASS = "res/string_date/gamescript/ImageId.json";
	const std::string IMAGE_ID_ARRYNAME = "imageid";
	const std::string MUSIC_ID_FILEPASS = "res/string_date/gamescript/MusicId.json";
	const std::string MUSIC_ID_ARRYNAME = "musicid";
	const std::string OBJECT_ID_FILEPASS = "res/string_date/gamescript/ObjectId.json";
	const std::string OBJECT_ID_ARRYNAME = "ObjectId";
}
ApplicationGlobal::ApplicationGlobal()
{
	is_EndSpeakScript = true;
}

ApplicationGlobal::~ApplicationGlobal()
{}

bool ApplicationGlobal::Init()
{
	is_EndSpeakScript = true;

	image_pass_date = std::make_shared<ScriptsData>();

	image_pass_date->LoadJson( IMAGE_ID_FILEPASS,IMAGE_ID_ARRYNAME );

	music_pass_date = std::make_shared<ScriptsData>();

	music_pass_date->LoadJson( MUSIC_ID_FILEPASS,MUSIC_ID_ARRYNAME );

	object_pass_date = std::make_shared<ScriptsData>();

	object_pass_date->LoadJson( OBJECT_ID_FILEPASS,OBJECT_ID_ARRYNAME );

	// SE‚Ì–‘O“Ç‚İ‚İ
	_se["pull"] = ResourceServer::LoadSoundMem( "res/sound/AAA/ˆø‚Á‚±”²‚¯‚é‰¹/pull.wav" );
	_se["AAA_death"] = ResourceServer::LoadSoundMem( "res/sound/AAA/‘Î‹ó–C”š”­€–S‰¹/enemy_death.wav" );

	_se["comm_start"] = ResourceServer::LoadSoundMem( "res/sound/communication/communication_start.wav" );

	_se["gunship_death"] = ResourceServer::LoadSoundMem( "res/sound/gunship/gunship_explosion/gunship_explosion.wav" );
	//_se["gunship_move"] = ResourceServer::LoadSoundMem( "res/sound/gunship/gunship_move/gunship_turning.wav" );

	_se["player_object_crash"] = ResourceServer::LoadSoundMem( "res/sound/player/ƒwƒŠ‚ªŒš•¨‚ÉÕ“Ë‚·‚é‰¹/heli_object_crash.wav" );
	_se["player_hovering"] = ResourceServer::LoadSoundMem( "res/sound/player/ƒwƒŠƒzƒoƒŠƒ“ƒO/heli_hovering.wav" );
	_se["player_death"] = ResourceServer::LoadSoundMem( "res/sound/player/ƒwƒŠ€–S”š”­‰¹/heli_death_explosion.wav" );
	_se["player_pull_button"] = ResourceServer::LoadSoundMem( "res/sound/player/ˆø‚Á‚±”²‚«ƒ{ƒ^ƒ“‰¹/pull_button_push.wav" );

	_se["se_gunshot"]= ResourceServer::LoadSoundMem( "res/sound/player/’e–ò/’Êí’e/’Êí’e”­Ë‰¹/normal_bullet_fast.wav" );
	_se["se_gunlanding"] = ResourceServer::LoadSoundMem( "res/sound/player/’e–ò/’Êí’e/’Êí’e’¼Œ‚‰¹/normal_bullet_hit.wav" );
		return true;
}
