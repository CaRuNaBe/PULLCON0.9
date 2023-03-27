#include "EffectSpawnAmmo.h"
EffectSpawnAmmo::EffectSpawnAmmo( ApplicationBase& game,ModeMainGame& mode )
	:EffectBase( game,mode )
{
	Init();
	// リソースサーバーからハンドルを取得する
	ResourceServer::GetHandles( "effect_spawn_ammo",_grAllHandles );
	_animeMax = static_cast<int>(_grAllHandles.size());
}

EffectSpawnAmmo::~EffectSpawnAmmo()
{}

void EffectSpawnAmmo::Init()
{
	EffectBase::Init();

	_animeNo = 0;
	_animeCnt = 0;

}

bool EffectSpawnAmmo::Update()
{
	EffectBase::Update();

	if ( _animeCnt == _animeMax )
	{
		_mode.GetObjectServer3D().Del( *this );
	}

	_animeCnt++;
	return true;
}

bool EffectSpawnAmmo::Draw()
{
	EffectBase::Draw();
	SetWriteZBuffer3D( false );
	DrawBillboard3D( ToDX( _vPos ),0.5f,0.5f,2500.0f,0.f,_grAllHandles[_animeCnt % _animeMax],TRUE );
	SetWriteZBuffer3D( true );
	return true;
}