#include "EffectHitBlackSmoke.h"
EffectHitBlackSmoke::EffectHitBlackSmoke(ApplicationBase& game, int layer, ModeMainGame& mode)
	:EffectBase(game, layer, mode)
{
	Initialize();
	// リソースサーバーからハンドルを取得する
	ResourceServer::GetHandles("effect_hit_black_smoke", _grAllHandles);
	_animeMax = static_cast<int>(_grAllHandles.size());
}

EffectHitBlackSmoke::~EffectHitBlackSmoke()
{}

void EffectHitBlackSmoke::Initialize()
{
	EffectBase::Initialize();

	_animeNo = 0;
	_animeCnt = 0;

}

bool EffectHitBlackSmoke::Update()
{
	EffectBase::Update();
	if (_cnt % 2 == 0)
	{
		_animeCnt++;
	}
	_vPos.y += 50.f;
	if (_animeCnt == _animeMax)
	{
		_mode.GetObjectServer3D().Del(*this);
	}
	return true;
}

bool EffectHitBlackSmoke::Draw()
{
	EffectBase::Draw();
	SetWriteZBuffer3D(false);
	DrawBillboard3D(ToDX(_vPos), 0.5f, 0.5f, 2500.0f, 0.f, _grAllHandles[_animeCnt % _animeMax], TRUE);
	SetWriteZBuffer3D(true);
	return true;
}