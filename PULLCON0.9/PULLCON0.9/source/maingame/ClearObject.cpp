
#include "ClearObject.h"
#include "../mode/ModeGame.h"
#include "../mode/ModeMainGame.h"
namespace
{
	constexpr int GUNSHIP_ID = 12;
}
ClearObject::ClearObject( ApplicationBase& game,ModeBase& mode,float _radius )
	:base( game,mode )
{
	radius = _radius;
	Init();
}

ClearObject::~ClearObject()
{

}

void ClearObject::Init()
{
	base::Init();
	auto file_pass_data = std::make_unique<ScriptsData>();
	const std::string FILEPASS = "res/script/gamescript/ObjectId.json";
	const std::string ARRYNAME = "ObjectId";
	file_pass_data->LoadJson( FILEPASS,ARRYNAME );

	_handle = MV1LoadModel( file_pass_data->GetScriptLine( GUNSHIP_ID ).c_str() );

	_vObjective = {_vPos.x ,_vPos.y, _vPos.z};
	_vPos = {_vObjective.x - 5000.f, _vObjective.y, _vObjective.z};
	_vEvent = _vPos;
	_fScale = 3.f;
	_collision._fRadius = 1400.f * _fScale;
	_collisionEvent._fRadius = _collision._fRadius * 5.f * _fScale;

	_iLife = 100;

}

bool ClearObject::Update()
{
	base::Update();

	if ( !_pull )
	{
		_vObjective = {_vPos.x ,_vPos.y, _vPos.z};
		_vPos = {_vObjective.x + 5000.f, _vObjective.y, _vObjective.z + 5000.f};
		_pull = !_pull;
	}

	for ( auto&& obje : _mode.GetObjectServer3D().GetObjects() )
	{
		if ( obje->GetType() == Type::kPlayer
				 || obje->GetType() == Type::kBullet )
		{
			if ( obje->GetType() == Type::kPlayer )
			{

			}
			if ( obje->GetType() == Type::kBullet )
			{
				if ( IsHitObject( *obje ) )
				{
					if ( obje->_CT == 0 )
					{
						_CT = 10;
						_overlap = true;
						obje->Damage();
						_iLife -= obje->_iDamage;
					}
				}
			}
		}
	}

	// 極座標(r(length),θ(rad))
	float sx = _vPos.x - _vObjective.x;
	float sz = _vPos.z - _vObjective.z;
	float length = sqrt( sx * sx + sz * sz );
	float rad = atan2( sz,sx );
	// 角速度
	rad += utility::TwoPi / (24.f * 60.f);

	_vPos.x = _vObjective.x + cos( rad ) * length;
	_vPos.z = _vObjective.z + sin( rad ) * length;

	// フォワードベクトル
	_vDir.x = cos( rad );
	_vDir.z = sin( rad );
	_vDir.Normalized();

	if ( _iLife < 0 )
	{
		Damage( _mode );
	}

	_collision._fRadius = 1400.f * _fScale;
	_collisionEvent._fRadius = _collision._fRadius * 5.f * _fScale;
	_vEvent = _vPos;
	UpdateCollision();  // コリジョン更新

	return true;
}

void ClearObject::Damage( ModeBase& mode )
{
	((ModeMainGame&)mode)._clear = true;
	mode.GetObjectServer3D().Del( *this );
}

bool ClearObject::Draw()
{
	base::Draw();

	DrawSphere3D( ToDX( _vObjective ),100.f,8,GetColor( 255,0,0 ),GetColor( 0,0,0 ),TRUE );
	// モデル拡大
	MV1SetScale( _handle,VGet( _fScale,_fScale,_fScale ) );
	// モデル回転
	MV1SetRotationYUseDir( _handle,ToDX( _vDir ),0.f );
	// モデル移動
	MV1SetPosition( _handle,ToDX( _vPos ) );
	// モデル描画
	MV1DrawModel( _handle );

	// コリジョン描画
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
