#include "EffectHitPlayerFrame.h"
EffectHitPlayerFrame::EffectHitPlayerFrame( ApplicationBase& game,ModeMainGame& mode )
	:EffectBase( game,mode )
{
	Init();
	// リソースサーバーからハンドルを取得する
	ResourceServer::GetHandles( "effect_hit_player_frame",_grAllHandles );
	_animeMax = static_cast<int>(_grAllHandles.size());
}

EffectHitPlayerFrame::~EffectHitPlayerFrame()
{}

void EffectHitPlayerFrame::Init()
{
	EffectBase::Init();

	_animeNo = 0;
	_animeCnt = 0;

}

bool EffectHitPlayerFrame::Update()
{
	EffectBase::Update();

	if ( _animeCnt == _animeMax )
	{
		_mode.GetObjectServer3D().Del( *this );
	}
	if (_cnt % 2 == 0) {
		_animeCnt++;
	}
	return true;
}

bool EffectHitPlayerFrame::Draw()
{
	EffectBase::Draw();
	SetWriteZBuffer3D( false );
	//DrawBillboard3D(ConvWorldPosToScreenPos(ToDX( _vPos )),0.5f,0.5f,2500.0f,0.f,_grAllHandles[_animeCnt % _animeMax],TRUE );
	VECTOR ScreenPos = ConvWorldPosToScreenPos(ToDX(_vPos));
	DrawRotaGraph(static_cast<int>(ScreenPos.x), static_cast<int>(ScreenPos.y), 1.f, 0, _grAllHandles[_animeCnt % _animeMax], TRUE);
	SetWriteZBuffer3D( true );
	return true;
}