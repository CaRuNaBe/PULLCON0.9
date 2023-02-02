
#include "appframe.h"
#include "../mode/ModeGame.h"
#include "../mode/ModeMainGame.h"
#include "Player.h"
#include "Bullet.h"

namespace {
	const float CAMERATARGET_Y = 1000.f;  // �J�����̒����_�̊�{�ʒu�@�v���C���[�̍��W�{�v���C���[��Y���W�{CAMERATARGET_Y
	const vector4 CAMERADEFAULT_POS = { 0.f, 2500.f, -4000.f };   // �v���C���[�����_�Ƃ����Ƃ��̃J�����̃x�N�g��
}

Player::Player(ApplicationBase& game, ModeBase& mode)
	:base(game, mode)
{
	_handle = MV1LoadModel("res/player/3Dmodel/mv1/cg_PlayerHelicopter.mv1");
	_se = ResourceServer::LoadSoundMem("res/player/Audio/pull.wav");
	_seBullet = ResourceServer::LoadSoundMem("res/player/Audio/normal_bullet_fast.wav");
	// �@�f�t�H���g�̃t�H���g�ŁA�T�C�Y�S�O�A�����R�̃t�H���g���쐬
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

	// �J�����̐ݒ�
	_cam._vPos = _vPos + CAMERADEFAULT_POS;
	_cam._vTarget = { _vPos.x, _vPos.y + CAMERATARGET_Y, _vPos.z };
	_cam._clipNear = 100.f;
	_cam._clipFar = 30000000.f;

}

bool Player::Update() {
	base::Update();
	// NUM��ԂȂ�PLAY��ԂɈڍs����
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
					// �I�u�W�F�N�g�܂ňړ�����
					vector4 objective = obje->_vPos;
					// �΋�C�p�[�c�̌��ŕϓ�������
					objective.y += _collision._fRadius + static_cast<float>(_iPieces + 1) * obje->_collision._fRadius;
					vector4 dir = objective - _vPos;
					dir.Normalized();
					_vPos += dir * static_cast<float>(_CT);
					if (_CT == 0) {
						_vPos = objective;
					}
				}
				if (obje->_finish == true) {
					// �΋�C�Ɏw��ʒu��_�킹��
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

	// �J�����X�V	
	CameraUpdate();

	if (_statePlayer == State::PLAY) {

		_finish = false;
		// �R������
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

		// �J�����̌����Ă���p�x���擾
		float sx = _cam._vPos.x - _cam._vTarget.x;
		float sy = _cam._vPos.y - _cam._vTarget.y;
		float sz = _cam._vPos.z - _cam._vTarget.z;
		float length3D = sqrt(sx * sx + sy * sy + sz * sz);
		float camerad = atan2(sz, sx);
		float theta = acos(sy / length3D);
		float rad = 0;

		//�L�����̏㏸���~
		int diry = 0;
		if (_game.Getinput().GetKeyXinput(XINPUT_BUTTON_A)) { diry += 1; }     // A
		if (_game.Getinput().GetKeyXinput(XINPUT_BUTTON_B)) { diry += -1; }     // B

		//�L�����̈ړ�
		vector4 dir = { -(_game.Getinput().GetLstickY()),0,_game.Getinput().GetLstickX() };   // int�l������

		float length = 0.f;
		dir.Normalized();
		if (dir.Lenght() > 0.f) { length = _fSpeed; }
		rad = atan2(dir.z, dir.x);
		dir.y += diry * _fSpeed;
		dir.x = cos(rad + camerad) * length;
		dir.z = sin(rad + camerad) * length;
		_vPos += dir;

		// �J�������Ǐ]������
		_cam._vPos += dir;
		_cam._vTarget += dir;

		// �e�ۂ̌����x�N�g���ݒ�
		vector4 v = { -1.f, 0.f, 0.f };
		rad = atan2(v.z, v.x);
		v.x = cos(rad + camerad);
		v.z = sin(rad + camerad);
		v.y = sin(_fRotatX);
		_vDir = v;

		if (_game.Getinput().XinputEveryOtherRightTrigger(1)) {  // RT
			if (_cnt % 20 == 0) {
				// SE�Đ�
				ChangeVolumeSoundMem(255 * 40 / 100, _seBullet);
				PlaySoundMem(_seBullet, DX_PLAYTYPE_BACK);
			}
			// �e����
			_fire = true;
			AddBullet();
			if (_game.Getinput().XinputEveryOtherRightTrigger(1)) {  // RT
				AddBullet();
			}

			// �w��ʒu�ݒ�
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

			// �����������J��
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
				// �����_�̈ړ�
				_cam._vTarget -= move;
				if (_finish) {
					// �㏸������
					_vPos.y += _fSpeed;
					_cam._vTarget.y += _fSpeed;
					if (_CT == 1) {
						// PLAY��ԂɑJ��
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
						// ��������������
						ChangeVolumeSoundMem(255 * 40 / 100, _se);
						PlaySoundMem(_se, DX_PLAYTYPE_BACK);
						_CT = 30;
						_finish = true;
						_push = 0;
					}
				}
			}

		}

		UpdateCollision();   // �R���W�����X�V

		if (_ST == 0) {
			_isHit = false;
		}

		// �J�����ݒ�X�V
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

		// �����_��`��
		float linelength = 100.f;
		DrawLine3D(VAdd(ToDX(_cam._vTarget), VGet(-linelength, 0, 0)), VAdd(ToDX(_cam._vTarget), VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(ToDX(_cam._vTarget), VGet(0, -linelength, 0)), VAdd(ToDX(_cam._vTarget), VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(ToDX(_cam._vTarget), VGet(0, 0, -linelength)), VAdd(ToDX(_cam._vTarget), VGet(0, 0, linelength)), GetColor(0, 0, 255));

		// ���f���̉�]�l
		float rX = utility::degree_to_radian(5.f);   // �����������
		if (_statePlayer == State::EVENT) {
			// �������������
			MV1SetRotationXYZ(_handle, VGet(rX, _fRotatY, 0.0f));
		}
		else {
			rX += _fRotatX;   // �J�����𓮂��������v���X
			MV1SetRotationXYZ(_handle, VGet(rX, _fRotatY, 0.0f));
		}
		// ���f���g��
		MV1SetScale(_handle, VGet(_fScale, _fScale, _fScale));
		// �ʒu
		MV1SetPosition(_handle, ToDX(_vPos));
		// ���C�e�B���O�v�Z
		// ���f���`��
		SetUseLighting(FALSE);
		MV1DrawModel(_handle);
		// �΋�C�̑_���ʒu������
		DrawSphere3D(ToDX(_vTarget), 100.f, 8, GetColor(255, 0, 0), GetColor(0, 0, 0), TRUE);
		SetUseLighting(TRUE);
		// �v���C���[�̒e�̋O����`��
		DrawLine3D(ToDX(_vPos), ToDX(_vTarget), GetColor(255, 0, 0));

		// �R���W�����`��
		if (!((ModeMainGame&)_mode)._dbgCollisionDraw) {
			vector4 color = { 255, 255, 255 };
			if (_isHit) { color = { 255, 0, 0 }; }
			DrawCollision(color);
		}
		VECTOR Pos = ConvWorldPosToScreenPos(ToDX(_vPos));
		if (_isHit) {
			// �쐬�����t�H���g�ŉ�ʍ���ɁwCLEAR�x�Ɖ��F�̕������`�悷��
			DrawStringToHandle(static_cast<int>(Pos.x), static_cast<int>(Pos.y), "H I T!!", GetColor(255, 255, 255), _handlefont);
		}

		// �f�o�b�N�\�L
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
			// ������������Ԃ̃J����
			EventCamera();
			return;
		}

		// �O�����ɍ��W(r(length3D),��(theta),��(camerad))
		float sx = _cam._vPos.x - _cam._vTarget.x;
		float sy = _cam._vPos.y - _cam._vTarget.y;
		float sz = _cam._vPos.z - _cam._vTarget.z;
		float length3D = sqrt(sx * sx + sy * sy + sz * sz);
		float camerad = atan2(sz, sx);
		float theta = acos(sy / length3D);


		// �p�x�ύX  ���f��������������
		// Y����]
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

		float limitrad = utility::radian_to_degree(theta);  // �x���@�ɕϊ�
		// X����]
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

		// �J�����ʒu
		_cam._vPos.y = _cam._vTarget.y + cos(theta) * length3D;
		_cam._vPos.x = _cam._vTarget.x + length3D * sin(theta) * cos(camerad);
		_cam._vPos.z = _cam._vTarget.z + length3D * sin(theta) * sin(camerad);

	}

	void Player::EventCamera() {

		// �O�����ɍ��W(r(length3D),��(theta),��(camerad))
		float sx = _cam._vPos.x - _vPos.x;
		float sy = _cam._vPos.y - _vPos.y;
		float sz = _cam._vPos.z - _vPos.z;
		float length3D = sqrt(sx * sx + sy * sy + sz * sz);
		float camerad = atan2(sz, sx);
		float theta = acos(sy / length3D);

		// �p�x�ύX
		// Y����]
		camerad = _fRotatY + utility::PI * 5.f / 6.f;

		// X����]
		//float degree = 100.f;
		//theta = utility::degree_to_radian(degree);

		float length = 500.f;
		length3D += length * static_cast<float>(_iPieces);

		// �J�����ʒu
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