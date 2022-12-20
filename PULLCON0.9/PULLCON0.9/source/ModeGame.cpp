
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

ModeGame::ModeGame( ApplicationBase& game,int layer )
	:base( game,layer )
{
	_handle = MV1LoadModel( "res/HelicopterBody.mv1" );
	_handleSkySphere = MV1LoadModel( "res/SkySphere/skysphere.mv1" );
	// プレイヤー
	_vPos = {0, 0, 0};
	// カメラの設定（わかりやすい位置に）
	_cam._vPos = VGet( 0,200.f,-1000.f );
	_cam._vTarget = VGet( 0,300.f,0 );
	_cam._clipNear = 2.f;
	_cam._clipFar = 15000.f;
};

ModeGame::~ModeGame()
{};

bool ModeGame::Initialize()
{
	if ( !base::Initialize() )
	{
		return false;
	}
	return true;
}

bool ModeGame::Update()
{
	base::Update();
	
	return true;
}

bool ModeGame::Draw()
{
	base::Draw();
	return true;
}

