
#include "appframe.h"
#include "../mode/ModeGame.h"
#include "../mode/ModeMainGame.h"
#include "Player.h"
#include "Bullet.h"

namespace {
	const float CAMERATARGET_Y = 1000.f;  // カメラの注視点の基本位置　プレイヤーの座標＋プレイヤーのY座標＋CAMERATARGET_Y
	const vector4 CAMERADEFAULT_POS = { 0.f, 2500.f, -4000.f };   // プレイヤーを原点としたときのカメラのベクトル
}

Player::Player(ApplicationBase& game, ModeBase& mode)
	:base(game, mode)
{
	_handle = MV1LoadModel("res/player/3Dmodel/mv1/cg_PlayerHelicopter.mv1");
	_se = ResourceServer::LoadSoundMem("res/player/Audio/pull.wav");
	_seBullet = ResourceServer::LoadSoundMem("res/player/Audio/normal_bullet_fast.wav");
	// 　デフォルトのフォントで、サイズ４０、太さ３のフォントを作成
	_handlefont = CreateFontToHandle(NULL, 40, 3);

	Init();
}

Player::~Player() {

}

void Player::Init() {
	base::Init();
	_statePlayer = State::NUM;

	_fSpeed = 90.f;
	_fRotatY = utility::PI;
	_iFuel = 100;
	_push = 0;
	_isHit = false;

	_vPos = { 0.f, 100.f,  -1000.f };
	_collision._fRadius = 500.f;

	// カメラの設定
	_cam._vPos = _vPos + CAMERADEFAULT_POS;
	_cam._vTarget = { _vPos.x, _vPos.y + CAMERATARGET_Y, _vPos.z };
	_cam._clipNear = 100.f;
	_cam._clipFar = 30000000.f;

}

bool Player::Update() {
	base::Update();
	// NUM状態ならPLAY状態に移行する
	if (_statePlayer == State::NUM) {
		_cam._vPos = _vPos + CAMERADEFAULT_POS;
		_cam._vTarget = { _vPos.x, _vPos.y + CAMERATARGET_Y, _vPos.z };
		_statePlayer = State::PLAY;
	}

	for (auto&& obje : _mode.GetObjectServer3D().GetObjects()) {
		if (obje->GetType() == Type::kEnemyAAA
			|| obje->GetType() == Type::kBullet) {
			if (obje->GetType() == Type::kEnemyAAA) {
				if (obje->_pull == true && _pull) {
					// オブジェクトまで移動する
					vector4 objective = obje->_vPos;
					// 対空砲パーツの個数で変動させる
					objective.y += _collision._fRadius + static_cast<float>(_iPieces + 1) * obje->_collision._fRadius;
					vector4 dir = objective - _vPos;
					dir.Normalized();
					_vPos += dir * static_cast<float>(_CT);
					if (_CT == 0) {
						_vPos = objective;
					}
				}
				if (obje->_finish == true) {
					// 対空砲に指定位置を狙わせる
					obje->_vTarget = _vTarget;
				}
				if (IsHitEvent(*obje)) {
					_event = true;
					if (_game.Getinput().GetTrgXinput(XINPUT_BUTTON_X) && !_pull) {
						_pull = true;
						obje->_pull = true;
						_CT = 10;
					}
				}
			}
			if (obje->GetType() == Type::kBullet) {
				if (IsHitObject(*obje)) {
					if (obje->_CT == 0) {
						_isHit = true;
						_ST = 20;
					}
				}
			}
		}
	}

	// カメラ更新	
	CameraUpdate();

	if (_statePlayer == State::PLAY) {

		_finish = false;
		// 燃料消費
		if (_cnt % 30 == 0) {
			--_iFuel;
			if (_iFuel < 0) {
				_iFuel = 0;
			}
		}
		((ModeMainGame&)_mode).SetXMax(_iFuel);

		if (_game.Getinput().GetTrgXinput(XINPUT_BUTTON_RIGHT_THUMB)) {
			_fSpeed += 30.f;
		}
		if (_game.Getinput().GetTrgXinput(XINPUT_BUTTON_LEFT_THUMB)) {
			_fSpeed -= 30.f;
		}

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
		if (_game.Getinput().GetKeyXinput(XINPUT_BUTTON_A)) { diry += 1; }     // A
		if (_game.Getinput().GetKeyXinput(XINPUT_BUTTON_B)) { diry += -1; }     // B

		//キャラの移動
		vector4 dir = { -(_game.Getinput().GetLstickY()),0,_game.Getinput().GetLstickX() };   // int値が入る

		float length = 0.f;
		dir.Normalized();
		if (dir.Lenght() > 0.f) { length = _fSpeed; }
		rad = atan2(dir.z, dir.x);
		dir.y += diry * _fSpeed;
		dir.x = cos(rad + camerad) * length;
		dir.z = sin(rad + camerad) * length;
		_vPos += dir;

		// カメラも追従させる
		_cam._vPos += dir;
		_cam._vTarget += dir;

		// 弾丸の向きベクトル設定
		vector4 v = { -1.f, 0.f, 0.f };
		rad = atan2(v.z, v.x);
		v.x = cos(rad + camerad);
		v.z = sin(rad + camerad);
		v.y = sin(_fRotatX);
		_vDir = v;

		if (_game.Getinput().XinputEveryOtherRightTrigger(1)) {  // RT
			if (_cnt % 20 == 0) {
				// SE再生
				ChangeVolumeSoundMem(255 * 40 / 100, _seBullet);
				PlaySoundMem(_seBullet, DX_PLAYTYPE_BACK);
			}
			// 弾生成
			_fire = true;
			AddBullet();
			if (_game.Getinput().XinputEveryOtherRightTrigger(1)) {  // RT
				AddBullet();
			}

			// 指定位置設定
			float distance = _collision._fRadius * 2.f * 15.f;
			v.x = cos(rad + camerad) * distance;
			v.z = sin(rad + camerad) * distance;
			v.y = sin(_fRotatX) * distance;
			_vTarget = _vPos + v;

			/*
			vector4 cursor = { 0.f,0.f,0.f };
			cursor.y = _cam._vTarget.y + sin(_fRotatX) * length3D;
			cursor.x = _cam._vTarget.x + length3D * cos(rad + camerad);
			cursor.z = _cam._vTarget.z + length3D * sin(rad + camerad);
			*/

			((ModeMainGame&)_mode).SetCursor(_vTarget);

			// 引っこ抜き遷移
			if (_pull && _CT == 0) {
				((ModeMainGame&)_mode)._transparence = true;
				_cam._vMemory = _cam._vPos - _cam._vTarget;
				_cam._vPos = _vPos + CAMERADEFAULT_POS;
				_statePlayer = State::EVENT;
			}

		}
	}
		else if (_statePlayer == State::EVENT) {
			vector4 move = { 0.f, 2.f, 0.f };
			if (_pull && _CT > 0) {
				// 注視点の移動
				_cam._vTarget -= move;
				if (_finish) {
					// 上昇させる
					_vPos.y += _fSpeed;
					_cam._vTarget.y += _fSpeed;
					if (_CT == 1) {
						// PLAY状態に遷移
						_pull = false;
						((ModeMainGame&)_mode)._transparence = false;
						_cam._vTarget = { _vPos.x, _vPos.y + CAMERATARGET_Y, _vPos.z };
						_cam._vPos = _cam._vTarget + _cam._vMemory;
						_statePlayer = State::PLAY;
					}
				}
			}

			if (_game.Getinput().GetTrgXinput(XINPUT_BUTTON_X)) {
				if (_pull && _CT == 0) {
					_CT = 10;
					++_push;
					if (_push == 6) {
						// 引っこ抜き完了
						ChangeVolumeSoundMem(255 * 40 / 100, _se);
						PlaySoundMem(_se, DX_PLAYTYPE_BACK);
						_CT = 30;
						_finish = true;
						_push = 0;
					}
				}
			}

		}

		UpdateCollision();   // コリジョン更新

		if (_ST == 0) {
			_isHit = false;
		}

		// カメラ設定更新
		if (_statePlayer == State::EVENT) {
			SetCameraPositionAndTarget_UpVecY(ToDX(_cam._vPosEvent), ToDX(_cam._vTarget));
		}
		else {
			SetCameraPositionAndTarget_UpVecY(ToDX(_cam._vPos), ToDX(_cam._vTarget));
		}
		SetCameraNearFar(_cam._clipNear, _cam._clipFar);

		return true;
	}

	bool Player::Draw() {
		base::Draw();

		// 注視点を描画
		float linelength = 100.f;
		DrawLine3D(VAdd(ToDX(_cam._vTarget), VGet(-linelength, 0, 0)), VAdd(ToDX(_cam._vTarget), VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(ToDX(_cam._vTarget), VGet(0, -linelength, 0)), VAdd(ToDX(_cam._vTarget), VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(ToDX(_cam._vTarget), VGet(0, 0, -linelength)), VAdd(ToDX(_cam._vTarget), VGet(0, 0, linelength)), GetColor(0, 0, 255));

		// モデルの回転値
		float rX = utility::degree_to_radian(5.f);   // 少し上向きに
		if (_statePlayer == State::EVENT) {
			// 引っこ抜き状態
			MV1SetRotationXYZ(_handle, VGet(rX, _fRotatY, 0.0f));
		}
		else {
			rX += _fRotatX;   // カメラを動かした分プラス
			MV1SetRotationXYZ(_handle, VGet(rX, _fRotatY, 0.0f));
		}
		// モデル拡大
		MV1SetScale(_handle, VGet(_fScale, _fScale, _fScale));
		// 位置
		MV1SetPosition(_handle, ToDX(_vPos));
		// ライティング計算
		// モデル描画
		SetUseLighting(FALSE);
		MV1DrawModel(_handle);
		// 対空砲の狙う位置を可視化
		DrawSphere3D(ToDX(_vTarget), 100.f, 8, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
		SetUseLighting(TRUE);
		// プレイヤーの弾の軌道を描画
		DrawLine3D(ToDX(_vPos), ToDX(_vTarget), GetColor(255, 0, 0));

		// コリジョン描画
		if (!((ModeMainGame&)_mode)._dbgCollisionDraw) {
			vector4 color = { 255, 255, 255 };
			if (_isHit) { color = { 255, 0, 0 }; }
			DrawCollision(color);
		}
		VECTOR Pos = ConvWorldPosToScreenPos(ToDX(_vPos));
		if (_isHit) {
			// 作成したフォントで画面左上に『CLEAR』と黄色の文字列を描画する
			DrawStringToHandle(static_cast<int>(Pos.x), static_cast<int>(Pos.y), "H I T!!", GetColor(255, 255, 255), _handlefont);
		}

		// デバック表記
		int x = 0, y = 0, size = 16;
		SetFontSize(size);
		DrawFormatString(x, y, GetColor(255, 0, 0), "Camera:"); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  target = (%5.2f, %5.2f, %5.2f)", _cam._vTarget.x, _cam._vTarget.y, _cam._vTarget.z); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 0), "  pos    = (%5.2f, %5.2f, %5.2f)", _cam._vPos.x, _cam._vPos.y, _cam._vPos.z); y += size;
		DrawFormatString(x, y, GetColor(255, 0, 255), "  feil = %d ", _iFuel); y += size;

		return true;
	}

	void Player::CameraUpdate() {

		if (_statePlayer == State::EVENT) {
			// 引っこ抜き状態のカメラ
			EventCamera();
			return;
		}

		// 三次元極座標(r(length3D),θ(theta),φ(camerad))
		float sx = _cam._vPos.x - _cam._vTarget.x;
		float sy = _cam._vPos.y - _cam._vTarget.y;
		float sz = _cam._vPos.z - _cam._vTarget.z;
		float length3D = sqrt(sx * sx + sy * sy + sz * sz);
		float camerad = atan2(sz, sx);
		float theta = acos(sy / length3D);


		// 角度変更  モデルも同期させる
		// Y軸回転
		if (_game.Getinput().GetRstickX() < -1000)
		{
			camerad += 0.02f;
			_fRotatY += -0.02f;
		}
		else if (_game.Getinput().GetRstickX() > 1000)
		{
			camerad += -0.02f;
			_fRotatY += 0.02f;
		}

		float limitrad = utility::radian_to_degree(theta);  // 度数法に変換
		// X軸回転
		if (_game.Getinput().GetRstickY() < -1000)
		{
			if (limitrad > 40.f) {
				theta += -0.02f;
				_fRotatX += -0.02f;
			}
		}
		else if (_game.Getinput().GetRstickY() > 1000)
		{
			if (limitrad < 100.f) {
				theta += 0.02f;
				_fRotatX += 0.02f;
			}
		}

		// カメラ位置
		_cam._vPos.y = _cam._vTarget.y + cos(theta) * length3D;
		_cam._vPos.x = _cam._vTarget.x + length3D * sin(theta) * cos(camerad);
		_cam._vPos.z = _cam._vTarget.z + length3D * sin(theta) * sin(camerad);

	}

	void Player::EventCamera() {

		// 三次元極座標(r(length3D),θ(theta),φ(camerad))
		float sx = _cam._vPos.x - _vPos.x;
		float sy = _cam._vPos.y - _vPos.y;
		float sz = _cam._vPos.z - _vPos.z;
		float length3D = sqrt(sx * sx + sy * sy + sz * sz);
		float camerad = atan2(sz, sx);
		float theta = acos(sy / length3D);

		// 角度変更
		// Y軸回転
		camerad = _fRotatY + utility::PI * 5.f / 6.f;

		// X軸回転
		//float degree = 100.f;
		//theta = utility::degree_to_radian(degree);

		float length = 500.f;
		length3D += length * static_cast<float>(_iPieces);

		// カメラ位置
		_cam._vPosEvent.y = _vPos.y + cos(theta) * length3D;
		_cam._vPosEvent.x = _vPos.x + length3D * sin(theta) * cos(camerad);
		_cam._vPosEvent.z = _vPos.z + length3D * sin(theta) * sin(camerad);

	}

	void Player::AddBullet() {
		vector4 vBullet = { _vPos.x, _vPos.y, _vPos.z };
		auto bullet = std::make_shared<Bullet>(_game, _mode);
		bullet->SetPosition(vBullet);
		bullet->SetDir(_vDir);
		_mode.GetObjectServer3D().Add(bullet);
	}