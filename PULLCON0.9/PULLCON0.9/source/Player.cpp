
#include "appframe.h"
#include "ModeGame.h"
#include "Player.h"
#include "Bullet.h"


Player::Player() 
	:base()
{
	_handle = MV1LoadModel("res/player/3Dmodel/mv1/cg_PlayerHelicopter.mv1");

	Init();
}

Player::~Player() {

}

void Player::Init() {
	base::Init();

	_speed = 30.f;
	_rotatX = 0.f;
	_rotatY = utility::PI;
	_collision._fRadius = 500.f;

	// カメラの設定
	_cam._vPos = { 0.f, 2500.f, -4000.f };
	_cam._vTarget = { 0.f, 1200.f, 0.f };
	_cam._clipNear = 2000.f;
	_cam._clipFar = 30000.f;

}

bool Player::Update(ApplicationBase& game, ModeBase& mode) {
	base::Update(game, mode);

	// カメラ更新	
	CameraUpdate(game);

	// カメラの向いている角度を取得
	float sx = _cam._vPos.x - _cam._vTarget.x;
	float sy = _cam._vPos.y - _cam._vTarget.y;
	float sz = _cam._vPos.z - _cam._vTarget.z;
	float length3D = sqrt(sx * sx + sy * sy + sz * sz);
	float camerad = atan2(sz, sx);
	float theta = acos(sy / length3D);
	float rad = 0;

	//キャラの上昇下降
	int diry = 0;
	if(game.Getinput().GetKeyXinput(XINPUT_BUTTON_A)) { diry += 1; }     // A
	if(game.Getinput().GetKeyXinput(XINPUT_BUTTON_B)) { diry += -1; }     // B

	//キャラの移動
	vector4 dir = { -(game.Getinput().GetLstickY()),0,game.Getinput().GetLstickX() };   // int値が入る

	float length = 0.f;
	dir.Normalized();
	if(dir.Lenght() > 0.f) { length = _speed; }
	rad = atan2(dir.z, dir.x);
	dir.y += diry * _speed;
	dir.x = cos(rad + camerad) * length;
	dir.z = sin(rad + camerad) * length;
	_vPos += dir;
	_cam._vPos += dir;
	_cam._vTarget += dir;

	vector4 v = { -1.f, 0.f, 0.f };
	rad = atan2(v.z, v.x);
	v.x = cos(rad + camerad);
	v.z = sin(rad + camerad);
	v.y = sin(_rotatX);

	if(game.Getinput().XinputEveryOtherRightTrigger(6)) {  // RT
		_vDir = v;
		AddBullet(mode);
	}

	UpdateCollision();

	vector4 cursor = { 0.f,0.f,0.f };
	cursor.y = _cam._vTarget.y + sin(_rotatX) * length3D;
	cursor.x = _cam._vTarget.x + length3D * cos(rad + camerad);
	cursor.z = _cam._vTarget.z + length3D * sin(rad + camerad);

	((ModeGame&)mode).SetCursor(cursor);

	return true;
}

bool Player::Draw(ApplicationBase& game, ModeBase& mode) {
	base::Draw(game, mode);
	// カメラ設定更新
	SetCameraPositionAndTarget_UpVecY(ToDX(_cam._vPos), ToDX(_cam._vTarget));
	SetCameraNearFar(_cam._clipNear, _cam._clipFar);

	float linelength = 100.f;
	DrawLine3D(VAdd(ToDX(_cam._vTarget), VGet(-linelength, 0, 0)), VAdd(ToDX(_cam._vTarget), VGet(linelength, 0, 0)), GetColor(255, 0, 0));
	DrawLine3D(VAdd(ToDX(_cam._vTarget), VGet(0, -linelength, 0)), VAdd(ToDX(_cam._vTarget), VGet(0, linelength, 0)), GetColor(0, 255, 0));
	DrawLine3D(VAdd(ToDX(_cam._vTarget), VGet(0, 0, -linelength)), VAdd(ToDX(_cam._vTarget), VGet(0, 0, linelength)), GetColor(0, 0, 255));

	// モデルの回転値
	float rX = _rotatX + utility::degree_to_radian(5.f);   // 少し上向きに
	MV1SetRotationXYZ(_handle, VGet(rX, _rotatY, 0.0f));
	// モデルの拡大値
	//MV1SetScale(_handle, VGet(0.3f, 0.3f, 0.3f));
	// 位置
	MV1SetPosition(_handle, ToDX(_vPos));
	MV1DrawModel(_handle);

	DrawCollision();

	// デバック表記
	int x = 0, y = 0, size = 16;
	SetFontSize(size);
	DrawFormatString(x, y, GetColor(255, 0, 0), "Camera:"); y += size;
	DrawFormatString(x, y, GetColor(255, 0, 0), "  target = (%5.2f, %5.2f, %5.2f)", _cam._vTarget.x, _cam._vTarget.y, _cam._vTarget.z); y += size;
	DrawFormatString(x, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _cam._vPos.x, _cam._vPos.y, _cam._vPos.z); y += size;
	float sx = _cam._vPos.x - _cam._vTarget.x;
	float sz = _cam._vPos.z - _cam._vTarget.z;
	float length = sqrt(sz * sz + sx * sx);
	float rad = atan2(sz, sx);
	float deg = utility::radian_to_degree(rad);
	// カメラの向いてる角度を求める
	float sy = _cam._vPos.y - _cam._vTarget.y;
	float length3D = sqrt(sx * sx + sy * sy + sz * sz);
	float theta = acos(sy / length3D);
	float toCamedeg = utility::radian_to_degree(theta);
	DrawFormatString(x, y, GetColor(255, 0, 0), "  len = %5.2f, deg = %5.2f,toCamedeg = %5.2f", length, deg, toCamedeg); y += size;

	return true;
}

void Player::CameraUpdate(ApplicationBase& game) {

	// ベクトルの大きさの変更
	if (game.Getinput().GetKeyXinput(XINPUT_BUTTON_RIGHT_SHOULDER)) {
		_cam._vTarget.x += 20.f; _cam._vPos.x += 20.f;
	}  // RB
	if (game.Getinput().GetKeyXinput(XINPUT_BUTTON_LEFT_SHOULDER)) {
		_cam._vTarget.x -= 20.f; _cam._vPos.x -= 20.f;
	}   // LB
	if (game.Getinput().GetKeyXinput(XINPUT_BUTTON_START)) {
		_cam._vTarget.y += 20.f; _cam._vPos.y += 20.f;
	}  // RB
	if (game.Getinput().GetKeyXinput(XINPUT_BUTTON_BACK)) {
		_cam._vTarget.y -= 20.f; _cam._vPos.y -= 20.f;
	}   // LB
	
	// 三次元極座標(r(length3D),θ(theta),φ(camerad))
	float sx = _cam._vPos.x - _cam._vTarget.x;
	float sy = _cam._vPos.y - _cam._vTarget.y;
	float sz = _cam._vPos.z - _cam._vTarget.z;
	float length3D = sqrt(sx * sx + sy * sy + sz * sz);
	float camerad = atan2(sz, sx);
	float theta = acos(sy / length3D);


	// 角度変更
	// Y軸回転
	if(game.Getinput().GetRstickX() < -1000)
	{
		camerad += 0.02f;
		_rotatY += -0.02f;
	} 
	else if(game.Getinput().GetRstickX() > 1000)
	{
		camerad += -0.02f;
		_rotatY += 0.02f;
	}

	float limitrad = utility::radian_to_degree(theta);  // 度数法に変換

	// X軸回転
	if(game.Getinput().GetRstickY() < -1000)
	{
		if(limitrad > 60.f) {
			theta += -0.02f;
			_rotatX += -0.02f;
		}
	} else if(game.Getinput().GetRstickY() > 1000)
	{
		if(limitrad < 130.f) {
			theta += 0.02f;
			_rotatX += 0.02f;
		}
	}

	// カメラ位置
	_cam._vPos.y = _cam._vTarget.y + cos(theta) * length3D;
	_cam._vPos.x = _cam._vTarget.x + length3D * sin(theta) * cos(camerad);
	_cam._vPos.z = _cam._vTarget.z + length3D * sin(theta) * sin(camerad);

}

void Player::AddBullet(ModeBase& mode) {
	vector4 vBullet = { _vPos.x, _vPos.y, _vPos.z};
	auto bullet = std::make_shared<Bullet>();
	bullet->SetPosition(vBullet);
	bullet->SetDir(_vDir);
	mode.GetObjectServer3D().Add(bullet);
}