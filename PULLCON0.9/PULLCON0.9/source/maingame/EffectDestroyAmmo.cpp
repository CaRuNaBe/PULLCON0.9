#include "EffectDestroyAmmo.h"
EffectDestroyAmmo::EffectDestroyAmmo( ApplicationBase& game,ModeMainGame& mode )
	:EffectBase( game,mode )
{
	Init();
	// ���\�[�X�T�[�o�[����n���h�����擾����
	ResourceServer::GetHandles( "effect_destroy_ammo",_grAllHandles );
	_animeMax = static_cast<int>(_grAllHandles.size());
}

EffectDestroyAmmo::~EffectDestroyAmmo()
{}

void EffectDestroyAmmo::Init()
{
	EffectBase::Init();

	_animeNo = 0;
	_animeCnt = 0;

}

bool EffectDestroyAmmo::Update()
{
	EffectDestroyAmmo::Update();

	if ( _animeCnt == _animeMax )
	{
		_mode.GetObjectServer3D().Del( *this );
	}
	_animeCnt++;
	return true;
}

bool EffectDestroyAmmo::Draw()
{
	EffectBase::Draw();
		// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D( false );
	DrawBillboard3D( ToDX( _vPos ),0.5f,0.5f,40000.0f,0.f,_grAllHandles[_animeCnt % _animeMax],TRUE );
		// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D( true );
	return true;
}
