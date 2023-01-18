#include "GameStage.h"
GameStage::GameStage()
	:base()
{
	_handle = MV1LoadModel( "res/stage/stage_file_1/mv1/cg_stage1.mv1" );

	Init();
}

GameStage::~GameStage()
{

}

void GameStage::Init()
{
	base::Init();


}

bool GameStage::Update( ApplicationBase& game,ModeBase& mode )
{
	base::Update( game,mode );



	return true;
}

bool GameStage::Draw( ApplicationBase& game,ModeBase& mode )
{
	base::Draw( game,mode );
	MV1DrawModel( _handle );
	return true;
}
