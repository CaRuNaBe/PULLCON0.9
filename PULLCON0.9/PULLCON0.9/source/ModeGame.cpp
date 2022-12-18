
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"

ModeGame::ModeGame(ApplicationBase& game, int layer)
	:base(game, layer)
{
	_handle = MV1LoadModel("res/HelicopterBody.mv1");
	_handleSkySphere = MV1LoadModel("res/SkySphere/skysphere.mv1");
	// プレイヤー
	_vPos = { 0, 0, 0 };
	// カメラの設定（わかりやすい位置に）
	_cam._vPos = VGet(0, 200.f, -1000.f);
	_cam._vTarget = VGet(0, 300.f, 0);
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
	//キャラの進む向きを求める
	int diry = 0;
	if(_game.Getinput().GetKeyXinput(XINPUT_BUTTON_A)) { diry += 1; }     // A
	if(_game.Getinput().GetKeyXinput(XINPUT_BUTTON_B)) { diry += -1; }     // B
	vector4 dir = { _game.Getinput().GetLstickX(),diry,_game.Getinput().GetLstickY() };

	dir.Normalized();
	auto spead = 5.0f;
	dir = dir * spead;
	//_vPos.add(dir);

	/*
	// 角度変更
	// Y軸回転
	float sx = _cam._vPos.x - _cam._vTarget.x;
	float sz = _cam._vPos.z - _cam._vTarget.z;
	float rad = atan2(sz,sx);
	float length = sqrt(sz * sz + sx * sx);

	if(_game.Getinput().GetKey(PAD_INPUT_LEFT))
	{
		rad -= 0.05f;
	};
	if(_game.Getinput().GetKey(PAD_INPUT_RIGHT))
	{
		rad += 0.05f;
	}

	_cam._vPos.x = _cam._vTarget.x + cos(rad) * length;
	_cam._vPos.z = _cam._vTarget.z + sin(rad) * length;

	// Y位置
	if(_game.Getinput().GetKey(PAD_INPUT_DOWN))
	{
		_cam._vPos.y -= 5.f;
	}
	if(_game.Getinput().GetKey(PAD_INPUT_UP))
	{
		_cam._vPos.y += 5.f;
	}
	
	// 移動方向を決める
	vector4 v = { 0,0,0 };
	float mvSpeed = 10.f;
	/*
	if(_game.Getinput().GetKey(PAD_INPUT_5)) { v.x = 1; }     // S
	if(_game.Getinput().GetKey(PAD_INPUT_8)) { v.x = -1; }		// W
	if(_game.Getinput().GetKey(PAD_INPUT_4)) { v.z = -1; }		// A
	if(_game.Getinput().GetKey(PAD_INPUT_6)) { v.z = 1; }			// D
	// vをrad分回転させる
	length = 0.f;
	if(VSize(v) > 0.f) { length = mvSpeed; }
	float vrad = atan2(v.z, v.x);
	v.x = cos(vrad + rad) * length;
	v.z = sin(vrad + rad) * length;
	


	v.y *= mvSpeed;
	_vPos = _vPos + v;
	*/
	return true;
}

bool ModeGame::Draw()
{
	base::Draw();

	SetBackgroundColor(0, 0, 0);
	// 3D基本設定
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	VECTOR vLightDir = VGet(-1.f, -1.f, 1.f);
	SetGlobalAmbientLight(GetColorF(0.f, 0.f, 0.f, 0.f));
	ChangeLightTypeDir(vLightDir);


	// 0(赤),0(緑),0(青)を中心に線を引く
#if _DEBUG
	{
		float linelength = 1000.f;
		VECTOR v = { 0, 0, 0 };
		DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}
#endif
	// カメラ設定更新
	SetCameraPositionAndTarget_UpVecY(_cam._vPos, _cam._vTarget);
	SetCameraNearFar(_cam._clipNear, _cam._clipFar);
	_objectServer.Draw(_game);
	// モデルの回転値
	MV1SetRotationXYZ(_handle, VGet(0.f, math::utility::PI, 0.f));
	// モデルの拡大値
	MV1SetScale(_handle, VGet(0.3f, 0.3f, 0.3f));
	// 位置
	MV1SetPosition(_handle, ToDX(_vPos));
	MV1DrawModel(_handle);
	MV1DrawModel(_handleSkySphere);
	return true;
}

