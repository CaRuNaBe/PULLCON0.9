#include "EffectHitPlayerFrame.h"
EffectHitPlayerFrame::EffectHitPlayerFrame( ApplicationBase& game,ModeMainGame& mode )
	:EffectBase( game,mode )
{
	Init();
	// ���\�[�X�T�[�o�[����n���h�����擾����
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

	_animeCnt++;
	return true;
}

bool EffectHitPlayerFrame::Draw()
{
	EffectBase::Draw();
	SetWriteZBuffer3D( false );
	DrawBillboard3D( ToDX( _vPos ),0.5f,0.5f,2500.0f,0.f,_grAllHandles[_animeCnt % _animeMax],TRUE );
	SetWriteZBuffer3D( true );
	return true;
}