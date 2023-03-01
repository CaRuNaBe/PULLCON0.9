#include "AreaSupply.h"
#include "../ApplicationGlobal.h"
#include "../mode/ModeMainGame.h"
namespace
{
	constexpr int SUPPLY_ID = 37;
}
AreaSupply::AreaSupply( ApplicationBase& game,ModeMainGame& mode,float _radius )
	:base( game,mode )
{
	_handle = ResourceServer::LoadMV1Model( gGlobal.object_pass_date->GetScriptLine( SUPPLY_ID ) );
	Init();
	_fRadius = _radius;
}

AreaSupply::~AreaSupply()
{}

void AreaSupply::Init()
{
	base::Init();
}

bool AreaSupply::Update()
{
	base::Update();

	for ( auto&& obje : _mode.GetObjectServer3D().GetObjects() )
	{
		if ( obje->GetType() == Type::kPlayer )
		{
			if ( Intersect( obje->_collision,_collisionEvent ) )
			{
				_event = true;
				if ( _cnt % 10 == 0 )
				{
					obje->_iFuel++;
					if ( obje->_iFuel > 100 )
					{
						obje->_iFuel = 100;
					}
				}
			}
		}
	}

	_collisionEvent._fRadius = _fRadius * _fScale;
	_vEvent = _vPos;
	UpdateCollision();  // �R���W�����X�V

	return true;
}

bool AreaSupply::Draw()
{
	base::Draw();
	// ���f���g��
	MV1SetScale( _handle,VGet( _fScale,_fScale,_fScale ) );
	// ���f���ړ�
	MV1SetPosition( _handle,ToDX( _vPos ) );
	// ���C�e�B���O�v�Z
	// ���f���`��
	SetUseLighting( FALSE );
	MV1DrawModel( _handle );
	SetUseLighting( TRUE );

	// �R���W�����`��
	if ( !((ModeMainGame&)_mode)._dbgCollisionDraw )
	{
		vector4 color = {255, 255, 255};
		DrawCollisionEvent( color );
		if ( _event )
		{
			color = {0, 255, 0};
			DrawCollisionEvent( color );
		}
	}

	return true;
}
