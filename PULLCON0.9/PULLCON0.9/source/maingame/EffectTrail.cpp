
#include "appframe.h"
#include "EffectTrail.h"

EffectTrail::EffectTrail()
	:base()
{

	_animeMax = 17;
	_grAllHandles.resize(_animeMax);
	ResourceServer::LoadDivGraph("res/player/Fx/fx_BlackSmoke/fx_BlackSmoke.png", _animeMax, 3, 6, 512, 512, _grAllHandles.data());

	Init();
}

EffectTrail::~EffectTrail() {

}

void EffectTrail::Init() {
	base::Init();

	_animeNo = 0;
	_animeCnt = 0;

}

bool EffectTrail::Update(ApplicationBase& game, ModeBase& mode) {
	base::Update(game, mode);

	if (_animeCnt == _animeMax) {
		mode.GetObjectServer3D().Del(*this);
	}

	_animeNo = _animeCnt % _animeMax;
	_grHandle = _grAllHandles[_animeNo];
	_animeCnt++;
	return true;
}

bool EffectTrail::Draw(ApplicationBase& game, ModeBase& mode) {
	base::Draw(game, mode);

	DrawBillboard3D(ToDX(_vPos), 0.5f, 0.5f, 200.0f, 0.f, _grHandle, TRUE);

	return true;
}
