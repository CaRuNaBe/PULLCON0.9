#include  "EnemyColumn.h"
#include  "EnemySkyhunter.h"
EnemyColumn::EnemyColumn(ApplicationBase& game,ModeMainGame& mode)
	:base(game, mode) {
	Init();
}

EnemyColumn::~EnemyColumn() {

}

void EnemyColumn::Init() {
	base::Init();
	_stateEnemyColumn = State::WAIT;

	_vPos = { 0.f, 10000.f, 50000.f };
	_iPieces = 3;
	_fSpeed = 150.f;
	_fScale = 2.0f;

	_collision._fRadius = 500.f * _fScale;
	_collisionEvent._fRadius = _collision._fRadius * 13.f * _fScale;
	_collisionSearch._fRadius = _collisionEvent._fRadius * 2.f;

	AddPieces();
}

bool EnemyColumn::Update() {
	base::Update();


	for (auto&& obje : _mode.GetObjectServer3D().GetObjects()) {
		if (obje->GetType() == Type::kPlayer) {
			if (IsSearch(*obje)) {
				if (_stateEnemyColumn == State::WAIT) {
					_vRelation = obje->_vPos;
					SetVelocity();
					_stateEnemyColumn = State::PLAY;
					_synchronize = !_synchronize;
				}
			}
			else {
				if (_ST == 0) {
					_vRelation = obje->_vPos;
					SetVelocity();
					_stateEnemyColumn = State::PLAY;
					_synchronize = !_synchronize;
					_ST = 300;
				}
			}
		}
	}

	// 速度分移動する
	if (_vPos.y < 6000.f && _vVelocity.y < 0.f) {
		_vVelocity.y = 0.f;
	}
	_vPos += _vVelocity * _fSpeed;

	if (_iPieces == 0) {
		Damage();
	}

	_collisionSearch._fRadius = _collisionEvent._fRadius * 2.f;
	UpdateCollision();  // コリジョン更新

	return true;
}

void EnemyColumn::Damage() {
	_mode.GetObjectServer3D().Del(*this);
}

bool EnemyColumn::Draw() {
	base::Draw();

	// コリジョン描画
	vector4 color = { 255,255,255 };
	if (!((ModeMainGame&)_mode)._dbgCollisionDraw) {
		color = { 255,0,255 };
		DrawCollisionSearch(color);
	}
	return true;
}

void EnemyColumn::SetVelocity() {
	// 三次元極座標
	float sx = _vRelation.x - _vPos.x;
	float sz = _vRelation.z - _vPos.z;
	float sy = _vRelation.y - _vPos.y;
	float length3D = sqrt(sx * sx + sy * sy + sz * sz);
	float rad = atan2(sz, sx);
	float theta = acos(sy / length3D);

	float randomDeg = static_cast<float>(utility::get_random(-30, 30));
	float randomRad = utility::degree_to_radian(randomDeg);
	// モデルの進行方向設定用
	_vVelocity.x = cos(rad + randomRad);
	_vVelocity.z = sin(rad + randomRad);
	_vVelocity.y = cos(theta);
	_vVelocity.Normalized();
}

void EnemyColumn::AddPieces() {
	for (auto i = 0; i < _iPieces; ++i) {
		auto skyhunter = std::make_shared<EnemySkyhunter>(_game, _mode, *this);
		skyhunter->SetPosition(_vPos);
		skyhunter->_iPart = i;
		skyhunter->_ST = 30 * i + 1;
		_mode.GetObjectServer3D().Add(skyhunter);
	}
}

