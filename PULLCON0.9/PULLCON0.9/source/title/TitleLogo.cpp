#include "TitleLogo.h"
#include "Dxlib.h"
TitleLogo::TitleLogo( ApplicationBase& game,int layer,ModeTitle& mode )
	: ActorTitle( game,layer,mode )
{
	_cg = ResourceServer::LoadGraph( "res/2D_image/title/ui_Title_Logo.png" );

	Initialize();
}

TitleLogo::~TitleLogo()
{
}

void TitleLogo::Initialize()
{
	ActorTitle::Initialize();

	_pos = {400.0f,100.0f};
	_size.x = 1202.0f;
	_size.y = 300.0f;
	_colPos.x = 0.0f;
	_colPos.y = 0.0f;
	_colSize.x = 1202.0f;
	_colSize.y = 300.0f;
	_spd = 0;
	_easing = math::Easing::GetMode( "Linear" );
}

bool TitleLogo::Update()
{
	ActorTitle::Update();
	float start = 100.f;
	float stop = 300.f;

	auto a = math::utility::TwoPi / 120.f;
	float b = std::sin( static_cast <float>(a * _cnt) );
	b *= 5;
	_pos.y = _easing( b,start,stop,60.f );
	UpdateCollision();	// コリジョン更新
	return true;
}


bool TitleLogo::Draw()
{
	ActorTitle::Draw();
	DrawGraph( _pos.IntX(),_pos.IntY(),_cg,TRUE );
	DrawCollision();	// コリジョン描画
	return true;
}


