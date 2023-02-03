#include "GameStage.h"

GameStage::GameStage( ApplicationBase& game,ModeBase& mode,int stageid )
	:base( game,mode )
{

	auto file_pass_data = std::make_unique<ScriptsData>();
	const std::string FILEPASS = "res/script/gamescript/ObjectId.json";
	const std::string ARRYNAME = "ObjectId";
	file_pass_data->LoadJson( FILEPASS,ARRYNAME );

	_handle = MV1LoadModel( file_pass_data->GetScriptLine( stageid ).c_str() );



	Init();
}

GameStage::~GameStage()
{

}

void GameStage::Init()
{
	base::Init();


}

bool GameStage::Update()
{
	base::Update();



	return true;
}

bool GameStage::Draw()
{
	base::Draw();
	MV1DrawModel( _handle );
	return true;
}
