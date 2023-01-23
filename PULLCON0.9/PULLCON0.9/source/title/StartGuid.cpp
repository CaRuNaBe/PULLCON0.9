#include "StartGuid.h"
#include "Dxlib.h"
StartGuid::StartGuid()
	: ActorBase2d()
{
	_cg = ResourceServer::LoadGraph( "res/title/ui_Title_StartMenuIcon.png" );

	Init();
}

StartGuid::~StartGuid()
{}

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

bool StartGuid::Update( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Update( game,mode );
	float start = 800.0f;
	float stop = 1000.0f;


	float pos = std::atan( std::sin( static_cast <float>((math::utility::TwoPi / 120.f) * _cnt) ) ) * 10;
	_pos.y = _easing( pos,start,stop,60.f );
	UpdateCollision();	// �R���W�����X�V
	return true;
}


bool StartGuid::Draw( ApplicationBase& game,ModeBase& mode )
{
	ActorBase2d::Draw( game,mode );
	DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	DrawCollision();	// �R���W�����`��
	return true;
}