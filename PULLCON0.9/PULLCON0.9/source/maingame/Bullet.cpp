
#include "Bullet.h"
#include "EffectTrail.h"


Bullet::Bullet( ApplicationBase& game,ModeMainGame& mode )
	:base( game,mode )
{
	_cgDarkPurple = ResourceServer::LoadMV1Model( "res/3D_model/ammo/AmmoModel_Ver1/Ammo_Blue.mv1" );
	_cgGreen = ResourceServer::LoadMV1Model( "res/3D_model/ammo/AmmoModel_Ver1/Ammo.mv1" );
	_cgPink = ResourceServer::LoadGraph( "res/2D_image/BulletBillBorad/BulletTexture_Pink.png" );
	_cgPurple = ResourceServer::LoadMV1Model( "res/3D_model/ammo/AmmoModel_Ver1/Ammo_Purple.mv1" );
	_cgYellow = ResourceServer::LoadMV1Model( "res/3D_model/ammo/AmmoModel_Ver1/Ammo.mv1" );
	_cg = 0;
	_handle = ResourceServer::LoadMV1Model( "res/3D_model/ammo/AmmoModel_Ver1/Ammo.mv1" );
	Init();
}

Bullet::~Bullet()
{
	MV1DeleteModel( _cgDarkPurple );
	MV1DeleteModel( _cgGreen );
	MV1DeleteModel( _cgPurple );
	MV1DeleteModel( _cgYellow );
	MV1DeleteModel( _handle );
}

void Bullet::Init()
{
	base::Init();

	_iType = 0;
	_iDamage = 1;
	_fSpeed = 800.f;

	_collision._fRadius = 50.f * _fScale;

	_CT = 10;
	_ST = 90;
}

bool Bullet::Update()
{
	base::Update();

	// 生存時間
	if ( _ST == 0 )
	{
		Damage();
	}

	// 設定された向きに進む
	vector4 _vd = _vDir;
	_vd *= _fSpeed;
	_vPos += _vd;

	_iDamage = _fScale;

	_collision._fRadius = 50.f * _fScale;
	UpdateCollision();    // コリジョンアップデート

	switch ( _iType )
	{
		case 1:
			_handle = _cgDarkPurple;
			break;
		case 2:
			_handle = _cgPink;
			break;
		case 3:
			_handle = _cgPurple;
			break;
		case 4:
			_handle = _cgYellow;
			break;
		default:
			_handle = _cgGreen;
			break;
	}

	return true;
}

void Bullet::Damage()
{
	_mode.GetObjectServer3D().Del( *this );
}

bool Bullet::Draw()
{
	base::Draw();

	float size = 150.f * _fScale;
	//DrawBillboard3D(ToDX(_vPos), 0.5f, 0.5f, size, 0.f, _cg, TRUE);

	float length3D = sqrt( _vDir.x * _vDir.x + _vDir.y * _vDir.y + _vDir.z * _vDir.z );
	float theta = acos( _vDir.y / length3D );
	MV1SetRotationZYAxis( _handle,VGet( _vDir.z,0.f,-(_vDir.x) ),VGet( 0.f,1.f,0.f ),theta - utility::PiOver2 );
	MV1SetPosition( _handle,ToDX( _vPos ) );
	MV1DrawModel( _handle );
	// コリジョン描画
	vector4 color = {255, 255, 255};
	if ( !((ModeMainGame&)_mode)._dbgCollisionDraw )
	{
		if ( _CT == 0 )
		{
			DrawCollision( color );
		}
	}
	return true;
}
