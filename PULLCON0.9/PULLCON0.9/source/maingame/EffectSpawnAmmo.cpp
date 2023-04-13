#include "EffectSpawnAmmo.h"
EffectSpawnAmmo::EffectSpawnAmmo(ApplicationBase& game, int layer, ModeMainGame& mode)
	:EffectBase(game, layer, mode)
{
	Initialize();
	// リソースサーバーからハンドルを取得する
	ResourceServer::GetHandles("effect_spawn_ammo", _grAllHandles);
	_animeMax = static_cast<int>(_grAllHandles.size());
}

EffectSpawnAmmo::~EffectSpawnAmmo()
{}

void EffectSpawnAmmo::Initialize()
{
	EffectBase::Initialize();
}

bool EffectSpawnAmmo::Update()
{
	EffectBase::Update();

	if (_animeNo == _animeMax)
	{
		_mode.GetObjectServer3D().Del(*this);
	}
	if (_animeCnt % 10 == 0)
	{
		++_animeNo;
	}
	_animeCnt++;

	return true;
}

bool EffectSpawnAmmo::Draw()
{
	EffectBase::Draw();
	SetWriteZBuffer3D(false);
	DrawBillboard3D(ToDX(_vPos), 0.5f, 0.5f, 15000.0f, 0.f, _grAllHandles[_animeNo], TRUE);
	SetWriteZBuffer3D(true);
	return true;
}