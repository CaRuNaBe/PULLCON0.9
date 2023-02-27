#include "StageObject.h"
#include "AreaNoEntry.h"
#include "../ApplicationGlobal.h"
StageObject::StageObject( ApplicationBase& game,ModeMainGame& mode,int objectid,int collision,int pieces_coll )
	:base( game,mode )
{

	_handle = ResourceServer::LoadMV1Model( gGlobal.object_pass_date->GetScriptLine( objectid ).c_str() );
	_iPiecesColl = pieces_coll;

	Init();
	if ( collision == 1 )
	{
		_coll = true;
	}
	else
	{
		_coll = false;
	}
}

StageObject::~StageObject()
{}

void StageObject::Init()
{
	base::Init();
	_stateStageObject = State::NUM;
	_iPieces = _iPiecesColl;
}

bool StageObject::Update()
{
	base::Update();
	_collision._fRadius = _fRadius * _fScale;
	UpdateCollision();
	if ( _stateStageObject == State::NUM )
	{
		AddCollision();
		_stateStageObject = State::STATE;
	}
	return true;
}

bool StageObject::Draw()
{
	base::Draw();
	// ƒ‚ƒfƒ‹Šg‘å
	MV1SetScale( _handle,VGet( _fScale,_fScale,_fScale ) );

	MV1SetPosition( _handle,math::ToDX( _vPos ) );
	// ƒRƒŠƒWƒ‡ƒ“•`‰æ
	vector4 color = {255, 0, 255};
	SetUseLighting( FALSE );
	// ƒ‚ƒfƒ‹•`‰æ
	MV1DrawModel( _handle );
	SetUseLighting( TRUE );
	DrawCollisionObject( color );
	return true;
}

void StageObject::AddCollision()
{
	vector4 areaPos = _vPos;
	for ( auto i = 1; i < _iPieces; ++i )
	{
		areaPos.y = _collision._fRadius * 2.f * i;
		auto area = std::make_shared<AreaNoEntry>( _game,_mode );
		area->SetPosition( areaPos );
		area->SetCollisionRadius( _collision._fRadius );
		area->_fScale = _fScale;
		_mode.GetObjectServer3D().Add( area );
	}
}
