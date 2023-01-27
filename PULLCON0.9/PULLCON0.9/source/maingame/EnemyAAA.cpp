#include "appframe.h"
#include "EnemyAAA.h"
#include "Bullet.h"
#include "../mode/ModeMainGame.h"

EnemyAAA::EnemyAAA()
	:base()
{
	_handle_body = MV1LoadModel("res/enemy/AAA/canon_mk1/mvi/cg_Canon_Mk1_dodai.mv1");
	_handle_turret = MV1LoadModel("res/enemy/AAA/canon_mk1/mvi/cg_Canon_Mk1_houtou.mv1");

	Init();
}

EnemyAAA::~EnemyAAA() {

}

void EnemyAAA::Init() {
	base::Init();
	_stateAAA = State::PLAY;

	_collision._fRadius = 300.f;
	_collisionEvent._fRadius = 500.f;
	_vEvent = { 10000.f, 10000.f, 10000.f };

	_iType = 0;
	_iPossession = 0;
	_fAxialX = 0.f;
	_fAxialY = 0.f;

	_CT = 30;
}

bool EnemyAAA::Update(ApplicationBase& game, ModeBase& mode) {
	base::Update(game,mode);

	for (auto&& obje : mode.GetObjectServer3D().GetObjects()) {
		if (obje->GetType() == Type::kPlayer
		 || obje->GetType() == Type::kBullet) {
			if (obje->GetType() == Type::kPlayer) {
				if(!_finish){
					if (Intersect(obje->_collision, _collisionEvent)) {
						// �C�x���g��ԂɈڍs������
						_event = true;
						_stateAAA = State::EVENT;
					}
					else {
						// �N����ԂɈȍ~
						_stateAAA = State::PLAY;
						if (_iType == 0) {
							_vTarget = obje->_vPos;
							// �e�Ƀo��������������
							float random = static_cast<float>(utility::get_random(0, 1000));
							_vTarget = { _vTarget.x + random, _vTarget.y + random, _vTarget.z + random };
						}
					}
				}
				if (obje->_finish && _pull) {
					// ���퉻�Ɉڍs
					_coll = false;
					_pull = false;
					_finish = true;
					_iPieces = obje->_iPieces;
					obje->_iPieces += _iPossession;
					_stateAAA = State::WEAPON;
				}
				if (_stateAAA == State::WEAPON) {
					// �v���C���[�Ɠ����𓯉�������
					_vPos = obje->_vPos;
					_vPos.y -= 2.f * _collision._fRadius + static_cast<float>(_iPieces) * _collision._fRadius;
					_fRotatY = obje->_fRotatY + utility::PiOver2;
				}
			}
			if (obje->GetType() == Type::kBullet) {
				if (IsHitObject(*obje)) {
					if (obje->_CT == 0) {
						_CT = 10;
						_overlap = true;
						obje->Damage(mode);
						//Damage(mode);
					}
				}
			}
		}
	}

	if(_stateAAA == State::PLAY){
		// �C�x���g�p�R���W�������ړ�
		float distance = _collision._fRadius + _collisionEvent._fRadius;
		_vEvent = { _vPos.x, _vPos.y + distance, _vPos.z };

		// �O�����ɍ��W(r(length3D),��(theta),��(rad))
		float sx = _vTarget.x - _vPos.x;
		float sy = 100.f + _vTarget.y - _vPos.y;   // �������_��
		float sz = _vTarget.z - _vPos.z;
		float length3D = sqrt(sx * sx + sy * sy + sz * sz);
		float rad = atan2(sz, sx);
		float theta = acos(sy / length3D);

		// �v���C���[��_��Ȃ��΋�C
		if (_iType == 1) {
			rad = utility::degree_to_radian(_fAxialY);
			theta = utility::degree_to_radian(_fAxialX);
			_fRotatX = theta;
		}

		// �e�̐i�s�����̌�����ݒ肷��
		_vDir.x = cos(rad);
		_vDir.z = sin(rad);
		_vDir.y = cos(theta);
		_vDir.Normalized();

		if (_CT == 0) {
			AddBullet(mode);
			_CT = 10;
		}

		// Y����]
		_fRotatY = -rad;
		// X����]
		float rX = cos(theta);
		float degree = utility::radian_to_degree(rX);
		if (degree >= 0.f && degree <= 40.f) {
			if (_iType == 0) {
				_fRotatX = rX;
			}
		}
	}
	else if(_stateAAA == State::WEAPON){
		// �O�����ɍ��W(r(length3D),��(theta),��(rad))
		float sx = _vTarget.x - _vPos.x;
		float sy = _vTarget.y - _vPos.y;
		float sz = _vTarget.z - _vPos.z;
		float length3D = sqrt(sx *sx +sy * sy + sz * sz);
		float rad = atan2(sz, sx);
		float theta = acos(sy / length3D);

		// �e�̐i�s�����̌�����ݒ肷��
		_vDir.x = cos(rad);
		_vDir.z = sin(rad);
		_vDir.y = cos(theta);
		_vDir.Normalized();

		if (_CT == 0) {
			AddBullet(mode);
			_CT = 10;
		}

		// X����]
		float rX = cos(theta);
		float degree = utility::radian_to_degree(rX);
		if (degree >= 0.f && degree <= 40.f) {
			_fRotatX = rX;
		}
	}

	UpdateCollision();   // �R���W�����A�b�v�f�[�g

	return true;
}

void EnemyAAA::Damage(ModeBase& mode) {
	mode.GetObjectServer3D().Del(*this);
}

bool EnemyAAA::Draw(ApplicationBase& game, ModeBase& mode) {
	base::Draw(game, mode);

	VECTOR pos = ToDX(_vPos);
	// ���f����]
	MV1SetRotationXYZ(_handle_body, VGet(0.f,_fRotatY,0.f));
	MV1SetRotationZYAxis(_handle_turret, VGet(-(_vDir.z), 0.f, _vDir.x), VGet(0.f, 1.f, 0.f), _fRotatX);
	// ���f���ړ�
	MV1SetPosition(_handle_body, pos);
	MV1SetPosition(_handle_turret, VGet(pos.x, pos.y + 40.f, pos.z));
	// ���f���`��
	MV1DrawModel(_handle_body);
	MV1DrawModel(_handle_turret);

	// �R���W�����`��
	if (!((ModeMainGame&)mode)._dbgCollisionDraw) {
		if (_coll) {
			vector4 color = { 255, 255, 255 };
			DrawCollision(color);
			if (!_finish) {
				DrawCollisionEvent(color);
			}
			if (_overlap) {
				color = { 255, 0, 0 };
				DrawCollision(color);
			}
			if (_event) {
				color = { 0, 255, 0 };
				DrawCollisionEvent(color);
			}
		}
	}

	return true;
}

void EnemyAAA::AddBullet(ModeBase& mode) {
	vector4 vBullet = { _vPos.x, _vPos.y + 100.f, _vPos.z };
	auto bullet = std::make_shared<Bullet>();
	bullet->SetPosition(vBullet);
	bullet->SetDir(_vDir);
	mode.GetObjectServer3D().Add(bullet);
}