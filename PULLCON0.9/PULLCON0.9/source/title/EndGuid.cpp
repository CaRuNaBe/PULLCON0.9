#include "EndGuid.h"
#include "Dxlib.h"
EndGuid::EndGuid( ApplicationBase& game,int laysr,ModeTitle& mode ): ActorTitle( game,layer,mode )
{
	_cg = ResourceServer::LoadGraph( "res/2D_image/title/ui_Titlle_EndMenuIcon.png" );

	Initialize();
}

EndGuid::~EndGuid()
{
}

void EndGuid::Initialize()
{
	ActorTitle::Initialize();

	_pos = {1370.0f,800.0f};
	_size = {91.0f,86.0f};
	_colPos = {0.0f,0.0f};
	_colSize = {91.0f,86.0f};
	_spd = 0;
	_easing = math::Easing::GetMode( "Linear" );
}

bool EndGuid::Update()
{
	ActorTitle::Update();
	float start = 800.0f;
	float stop = 1000.0f;

	auto a = math::utility::TwoPi / 120.f;
	float b = std::atan( std::sin( static_cast <float>(a * _cnt) ) );
	b *= 10;
	_pos.y = _easing( b,start,stop,60.f );
	UpdateCollision();	// �R���W�����X�V
	return true;
}


bool EndGuid::Draw()
{
	ActorTitle::Draw();
	DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	DrawCollision();	// �R���W�����`��
	return true;
}
