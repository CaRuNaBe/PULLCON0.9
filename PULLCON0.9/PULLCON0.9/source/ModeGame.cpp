
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

ModeGame::ModeGame(ApplicationBase& game,int layer)
	:base(game,layer)
{
	_handle = MV1LoadModel("res/HelicopterBody.mv1");
	// カメラの設定（わかりやすい位置に）
	_cam._vPos = VGet(0, 600.f, -1000.f);
	_cam._vTarget = VGet(0, 0, -1); 
	_cam._clipNear = 2.f;
	_cam._clipFar = 15000.f;
};

ModeGame::~ModeGame()
{};

bool ModeGame::Initialize()
{
	if(!base::Initialize())
	{
		return false;
	}
	return true;
}

bool ModeGame::Update()
{
	base::Update();
	_objectServer.Update(_game);
	return true;
}

bool ModeGame::Draw()
{
	base::Draw();
	// カメラ設定更新
	SetCameraPositionAndTarget_UpVecY(_cam._vPos, _cam._vTarget);
	SetCameraNearFar(_cam._clipNear, _cam._clipFar);
	_objectServer.Draw(_game);
	MV1DrawModel(_handle);
	return true;
}

