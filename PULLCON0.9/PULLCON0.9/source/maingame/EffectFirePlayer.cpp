#include "EffectFirePlayer.h"
EffectFirePlayer::EffectFirePlayer(ApplicationBase& game, int layer, ModeMainGame& mode)
	:EffectBase(game, layer, mode)
{
	Initialize();
	// リソースサーバーからハンドルを取得する
	ResourceServer::GetHandles("effect_fire_player", _grAllHandles);
	_animeMax = static_cast<int>(_grAllHandles.size());
}

EffectFirePlayer::~EffectFirePlayer()
{}

void EffectFirePlayer::Initialize()
{
	EffectBase::Initialize();
}

bool EffectFirePlayer::Update()
{
	EffectBase::Update();

	if (_animeCnt == _animeMax)
	{
		_mode.GetObjectServer3D().Del(*this);
	}
	_animeNo = _animeCnt % _animeMax;
	_animeCnt++;
	return true;
}

bool EffectFirePlayer::Draw()
{
	EffectBase::Draw();
	SetWriteZBuffer3D(false);
	DrawBillboard3D(ToDX(_vPos), 0.5f, 0.5f, 2500.0f, 0.f, _grAllHandles[_animeNo], TRUE);
	SetWriteZBuffer3D(true);
	return true;
}