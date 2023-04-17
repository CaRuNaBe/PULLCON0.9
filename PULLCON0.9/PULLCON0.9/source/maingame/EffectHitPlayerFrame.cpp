#include "EffectHitPlayerFrame.h"
EffectHitPlayerFrame::EffectHitPlayerFrame(ApplicationBase& game, int layer, ModeMainGame& mode)
	:EffectBase(game, layer, mode)
{
	Initialize();
	// リソースサーバーからハンドルを取得する
	ResourceServer::GetHandles("effect_hit_player_frame", _grAllHandles);
	_animeMax = static_cast<int>(_grAllHandles.size());
}

EffectHitPlayerFrame::~EffectHitPlayerFrame()
{}

void EffectHitPlayerFrame::Initialize()
{
	EffectBase::Initialize();

	_animeNo = 0;
	_animeCnt = 0;
}

bool EffectHitPlayerFrame::Update()
{
	EffectBase::Update();

	if (_animeCnt == _animeMax)
	{
		_mode.GetObjectServer3D().Del(*this);
	}
	if (_cnt % 2 == 0)
	{
		_animeCnt++;
	}
	return true;
}

bool EffectHitPlayerFrame::Draw()
{
	EffectBase::Draw();
	SetWriteZBuffer3D(false);
	//VECTOR ScreenPos = ConvWorldPosToScreenPos(ToDX(_vPos));
	DrawBillboard3D(ToDX(_vPos), 0.5f, 0.5f, 15000.0f, 0.f, _grAllHandles[_animeCnt % _animeMax], TRUE);
	/*DrawRotaGraph(static_cast<int>(ScreenPos.x), static_cast<int>(ScreenPos.y), 1.f, 0, _grAllHandles[_animeCnt % _animeMax], TRUE);*/
	SetWriteZBuffer3D(true);
	return true;
}