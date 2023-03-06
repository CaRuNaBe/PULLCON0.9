#include "AreaEnemySpawn.h"
#include "EnemyColumn.h"
#include "EnemyKobae.h"
#include "../mode/ModeMainGame.h"
#include "../ApplicationGlobal.h"
namespace
{
	constexpr int AREAENEMYSPAWN_ID = 14;
	constexpr int KOBAE_ID = 11;
	constexpr int SKYHUNTER_ID = 10;

}
AreaEnemySpawn::AreaEnemySpawn( ApplicationBase& game,ModeMainGame& mode,int spawnfream,int typeenemy )
	:base( game,mode )
{
	spawn_fream = spawnfream;
	_handle = ResourceServer::LoadMV1Model( gGlobal.object_pass_date->GetScriptLine( AREAENEMYSPAWN_ID ) );
	ResourceServer::LoadMV1Model( gGlobal.object_pass_date->GetScriptLine( KOBAE_ID ) );
	ResourceServer::LoadMV1Model( gGlobal.object_pass_date->GetScriptLine( SKYHUNTER_ID ) );

	Init();
}

AreaEnemySpawn::~AreaEnemySpawn()
{

}

void AreaEnemySpawn::Init()
{
	base::Init();
	_stateEnemySpawn = State::NUM;
	
	_isAddKobae = false;
	_vPos = { 0.f, 5000.f, 100000.f };
	_fScale = 3.f;
	_vEvent = _vPos;
	_collision._fRadius = 1500.f * _fScale;
	_collisionEvent._fRadius = _collision._fRadius * 20.f;

	_iLife = 10;
}

bool AreaEnemySpawn::Update()
{
	base::Update();

	if ( _stateEnemySpawn == State::NUM )
	{
		_collision._vCenter = _vPos;
		_collisionEvent._vCenter = _vPos;
		_stateEnemySpawn = State::WAIT;
	}

	for ( auto&& obje : _mode.GetObjectServer3D().GetObjects() )
	{
		if ( obje->GetType() == Type::kPlayer
			|| obje->GetType() == Type::kBullet )
		{
			if ( obje->GetType() == Type::kPlayer )
			{
				if ( Intersect( _collisionEvent,obje->_collision ) )
				{
					_coll = true;
					_fire = true;
				}
				else
				{
					_coll = false;
				}
			}
			if ( obje->GetType() == Type::kBullet )
			{
				if ( IsHitObject( *obje ) )
				{
					if ( obje->_CT == 0 )
					{
						_overlap = true;
						obje->Damage();
						//_iLife -= obje->_iDamage;
					}
				}
			}
		}
	}

	// ���Ԋu�ŃX�|�[��������
	if (_fire && _CT == 0) {
		switch (_iEnemyType) {
		case 1:
			AddEnemyColumn();
			break;
		case 2:
			AddEnemyKobae();
			break;
		case 3:
			if (_isAddKobae) {
				AddEnemyKobae();
			}
			else {
				AddEnemyColumn();
			}
			_isAddKobae = !_isAddKobae;
			break;
		default:
			break;
		}
		_CT = _iSpawnFream;
	}

	if ( _iLife < 0 )
	{
		Damage();
	}

	_collision._fRadius = 1500.f * _fScale;
	_collisionEvent._fRadius = _collision._fRadius * 20.f;
	_vEvent = _vPos;
	UpdateCollision();  // �R���W�����X�V

	return true;
}

bool AreaEnemySpawn::Draw()
{
	base::Draw();

	// ���f���g��
	MV1SetScale( _handle,VGet( _fScale,_fScale,_fScale ) );
	// ���f���ړ�
	MV1SetPosition( _handle,ToDX( _vPos ) );
	// ���f���`��
	MV1DrawModel( _handle );

	// �R���W�����`��
	vector4 color = {255,255,255};
	if ( !((ModeMainGame&)_mode)._dbgCollisionDraw )
	{
		DrawCollision( color );
		DrawCollisionEvent( color );
		if ( _overlap )
		{
			color = {255, 0, 0};
			DrawCollision( color );
		}
	}
	return true;
}

void AreaEnemySpawn::Damage()
{
	_mode.GetObjectServer3D().Del( *this );
}

void AreaEnemySpawn::AddEnemyColumn() {
	auto column = std::make_shared<EnemyColumn>(_game, _mode, _vPos);
	column->SetPosition(_vPos);
	_mode.GetObjectServer3D().Add(column);
}

void AreaEnemySpawn::AddEnemyKobae()
{
	auto kobae = std::make_shared<EnemyKobae>( _game,_mode );
	kobae->SetPosition( _vPos );
	_mode.GetObjectServer3D().Add( kobae );
}
