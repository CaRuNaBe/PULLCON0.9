#include "EffectFireGunship.h"
EffectFireGunship::EffectFireGunship( ApplicationBase& game,ModeMainGame& mode )
	:EffectBase( game,mode )
{
	Init();
	// ���\�[�X�T�[�o�[����n���h�����擾����
	ResourceServer::GetHandles( "effect_fire_gunship",_grAllHandles );
	_animeMax = static_cast<int>(_grAllHandles.size());
}

EffectFireGunship::~EffectFireGunship()
{}

void EffectFireGunship::Init()
{
	EffectBase::Init();

	_animeNo = 0;
	_animeCnt = 0;

}

bool EffectFireGunship::Update()
{
	EffectBase::Update();

	if ( _animeCnt == _animeMax )
	{
		_mode.GetObjectServer3D().Del( *this );
	}
	_animeCnt++;
	return true;
}

bool EffectFireGunship::Draw()
{
	EffectBase::Draw();
		// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D( false );
	DrawBillboard3D( ToDX( _vPos ),0.5f,0.5f,8000.0f,0.f,_grAllHandles[_animeCnt % _animeMax],TRUE );
		// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D( true );
	return true;
}