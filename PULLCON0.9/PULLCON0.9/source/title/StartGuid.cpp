#include "StartGuid.h"
#include "Dxlib.h"
StartGuid::StartGuid( ApplicationBase& game,ModeTitle& mode )
	: ActorBase2d( game,mode )
{
	_cg = ResourceServer::LoadGraph( "res/title/ui_Title_StartMenuIcon.png" );

	Init();
}

StartGuid::~StartGuid()
{
}

void StartGuid::Init()
{
	ActorBase2d::Init();

	_pos = {380.0f,800.0f};
	_size = {280.0f,86.0f};
	_colPos = {0.0f,0.0f};
	_colSize = {280.0f,86.0f};
	_spd = 0;
	_easing = Easing::GetMode( "Linear" );
}

bool StartGuid::Update()
{
	ActorBase2d::Update();
	float start = 800.0f;
	float stop = 1000.0f;


	float pos = std::atan( std::sin( static_cast <float>((math::utility::TwoPi / 120.f) * _cnt) ) ) * 10;
	_pos.y = _easing( pos,start,stop,60.f );
	UpdateCollision();	// コリジョン更新
	return true;
}


bool StartGuid::Draw()
{
	ActorBase2d::Draw();
	DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	DrawCollision();	// コリジョン描画
	return true;
}
