
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
	_push = 0;

	_collision._fRadius = 500.f;

	// カメラの設定
	_cam._vPos = { 0.f, 2500.f, -4000.f };
	_cam._vTarget = { 0.f, 1000.f, 0.f };
	_cam._clipNear = 2000.f;
	_cam._clipFar = 60000.f;

}

bool Player::Update(ApplicationBase& game, ModeBase& mode) {
	base::Update(game, mode);


	for (auto&& obje : mode.GetObjectServer3D().GetObjects()) {
		if (obje->GetType() == Type::kEnemyAAA
			|| obje->GetType() == Type::kBullet) {
			if (obje->GetType() == Type::kEnemyAAA) {
				if (_pull) {
					vector4 objective = obje->_vPos;
					objective.y += _collision._fRadius;
					objective.z -= obje->_collision._fRadius;
					vector4 dir = objective - _vPos;
					dir.Normalized();
					_vPos += dir * static_cast<float>(_CT);
					if (_CT == 0) {
						_vPos = objective;
					}
				}
				if (_finish) {
					obje->_vRelation = obje->_vPos - _vPos;
				}
				if (obje->_finish == true) {
					obje->_vDir = _vDir;
				}
				if (IsHitEvent(*obje)) {
					_event = true;
				}
			}
			if (obje->GetType() == Type::kBullet) {
				if (IsHitObject(*obje)) {
					if (obje->_CT == 0) {

					}
				}
			}
		}
	}

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

	// カメラも追従させる
	_cam._vPos += dir;
	_cam._vTarget += dir;

	if (game.Getinput().GetTrgXinput(XINPUT_BUTTON_X)) {
		if (_event && !_pull) {
			_pull = true;
			_CT = 30;
		}
		if (_pull && _CT == 0) {
			_vDir = { 0.f, 1.f, 0.f };
			_CT = 20;
			_push++;
			if (_push == 6) {
				_finish = true;
				_push = 0;
			}
		}
	}

	if (_pull && _CT > 0) {
		_cam._vTarget -= _vDir;
		if (_finish) {
			_vPos.y += _speed;
			_cam._vTarget.y += _speed;
			if (_CT == 1) {
				_pull == false;
			}
		}
	}

	// 弾丸の向きベクトル設定
	vector4 v = { -1.f, 0.f, 0.f };
	rad = atan2(v.z, v.x);
	v.x = cos(rad + camerad);
	v.z = sin(rad + camerad);
	v.y = sin(_rotatX);

	if(game.Getinput().XinputEveryOtherRightTrigger(1)) {  // RT
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
	// ライティング計算
	SetUseLighting(FALSE);
	MV1DrawModel(_handle);
	SetUseLighting(TRUE);

	vector4 color = { 255, 255, 255 };
	DrawCollision(color);

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

	if (_pull) {
		EventCamera(game);
		return;
	}
	
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
		if(limitrad > 40.f) {
			theta += -0.02f;
			_rotatX += -0.02f;
		}
	} else if(game.Getinput().GetRstickY() > 1000)
	{
		if(limitrad < 100.f) {
			theta += 0.02f;
			_rotatX += 0.02f;
		}
	}

	// カメラ位置
	_cam._vPos.y = _cam._vTarget.y + cos(theta) * length3D;
	_cam._vPos.x = _cam._vTarget.x + length3D * sin(theta) * cos(camerad);
	_cam._vPos.z = _cam._vTarget.z + length3D * sin(theta) * sin(camerad);

}

void Player::EventCamera(ApplicationBase& game) {

	// 三次元極座標(r(length3D),θ(theta),φ(camerad))
	float sx = _cam._vPos.x - _vPos.x;
	float sy = _cam._vPos.y - _vPos.y;
	float sz = _cam._vPos.z - _vPos.z;
	float length3D = sqrt(sx * sx + sy * sy + sz * sz);
	float camerad = atan2(sz, sx);
	float theta = acos(sy / length3D);

	// 角度変更
	// Y軸回転
	camerad = utility::PI * 5.f / 6.f;

	// X軸回転
	float degree = 100.f;
	theta = utility::degree_to_radian(degree);

	// カメラ位置
	_cam._vPos.y = _vPos.y + cos(theta) * length3D;
	_cam._vPos.x = _vPos.x + length3D * sin(theta) * cos(camerad);
	_cam._vPos.z = _vPos.z + length3D * sin(theta) * sin(camerad);

}

void Player::AddBullet(ModeBase& mode) {
	vector4 vBullet = { _vPos.x, _vPos.y, _vPos.z};
	auto bullet = std::make_shared<Bullet>();
	bullet->SetPosition(vBullet);
	bullet->SetDir(_vDir);
	mode.GetObjectServer3D().Add(bullet);
}