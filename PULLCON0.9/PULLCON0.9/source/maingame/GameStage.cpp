#include "GameStage.h"
namespace
{
	const auto STAGE_1 = 1;
	const auto STAGE_2 = 2;
	const auto STAGE_3 = 3;
	const auto STAGE_4 = 4;

}
GameStage::GameStage( ApplicationBase& game,ModeBase& mode,int stageid )
	:base( game,mode )
{

	switch ( stageid )
	{
		case STAGE_1:
			_handle = MV1LoadModel( "res/stage/stage_file_1/mv1/stage1/cg_stage1.mv1" );
			break;
		case STAGE_2:
			_handle = MV1LoadModel( "res/stage/stage_file_1/mv1/stage1/cg_stage1.mv1" );
			break;
		case STAGE_3:
			_handle = MV1LoadModel( "res/stage/stage_file_1/mv1/stage1/cg_stage1.mv1" );
			break;
		case STAGE_4:
			_handle = MV1LoadModel( "res/stage/stage_file_1/mv1/stage1/cg_stage1.mv1" );
			break;
		default:
			break;
	}

	Init();
}

GameStage::~GameStage()
{

}

void GameStage::Init()
{
	base::Init();


}

bool GameStage::Update( )
{
	base::Update( );



	return true;
}

bool GameStage::Draw( )
{
	base::Draw(  );
	MV1DrawModel( _handle );
	return true;
}
