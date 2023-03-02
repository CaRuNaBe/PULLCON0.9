
#include "appframe.h"
#include "ApplicationGlobal.h"

// ŽÀ‘Ì
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
{
}

bool ApplicationGlobal::Init()
{
	is_EndSpeakScript = true;

	image_pass_date = std::make_shared<ScriptsData>();

	image_pass_date->LoadJson( IMAGE_ID_FILEPASS,IMAGE_ID_ARRYNAME );

	music_pass_date = std::make_shared<ScriptsData>();

	music_pass_date->LoadJson( MUSIC_ID_FILEPASS,MUSIC_ID_ARRYNAME );

	object_pass_date = std::make_shared<ScriptsData>();

	object_pass_date->LoadJson( OBJECT_ID_FILEPASS,OBJECT_ID_ARRYNAME );

	return true;
}
