#include "EffectDefeatEnemy.h"
EffectDefeatEnemy::EffectDefeatEnemy( ApplicationBase& game,ModeMainGame& mode )
	:EffectBase( game,mode )
{
	Init();
	// リソースサーバーからハンドルを取得する
	ResourceServer::GetHandles( "effect_defeat_enemy",_grAllHandles );
	_animeMax = static_cast<int>(_grAllHandles.size());
}

EffectDefeatEnemy::~EffectDefeatEnemy()
{}

void EffectDefeatEnemy::Init()
{
	EffectBase::Init();

	_animeNo = 0;
	_animeCnt = 0;

}

bool EffectDefeatEnemy::Update()
{
	EffectBase::Update();

	if ( _animeCnt == _animeMax )
	{
		_mode.GetObjectServer3D().Del( *this );
	}
	_animeCnt++;
	return true;
}

bool EffectDefeatEnemy::Draw()
{
	EffectBase::Draw();

	DrawBillboard3D( ToDX( _vPos ),0.5f,0.5f,40000.0f,0.f,_grAllHandles[_animeCnt % _animeMax],TRUE );

	return true;
}