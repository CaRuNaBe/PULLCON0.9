#include "GameStage.h"
namespace
{
	const auto STAGE_1 = 1;
	const auto STAGE_2 = 2;
	const auto STAGE_3 = 3;
}
GameStage::GameStage( int stageid )
	:base()
{

	switch ( stageid )
	{
		case STAGE_1:
			_handle = MV1LoadModel( "res/stage/stage_file_1/mv1/stage1/cg_stage1.mv1" );
			break;

		default:
			break;
	}
	_handle = MV1LoadModel( "res/stage/stage_file_1/mv1/stage1/cg_stage1.mv1" );

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
