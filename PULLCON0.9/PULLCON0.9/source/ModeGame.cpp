
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeGame.h"
#include "Player.h"
#include "EnemyAAA.h"

ModeGame::ModeGame( ApplicationBase& game,int layer )
	:base( game,layer )
{
	_handleSkySphere = MV1LoadModel( "res/stage/skysphere/cg_stageSkymap_1.mv1" );
	//_handleSkySphere = MV1LoadModel( "res/stage_bg/SkySphere/skysphere.mv1" );
	_cg = ResourceServer::LoadGraph("res/cursor00.png");

	_vCursor = { 0.0f, 0.0f, 0.0f };

	// プレイヤー
	auto player = std::make_shared<Player>();
	_3D_objectServer.Add(player);
	auto enemyAAA = std::make_shared<EnemyAAA>();
	_3D_objectServer.Add(enemyAAA);

};

ModeGame::~ModeGame()
{};

bool ModeGame::Initialize()
{
	if ( !base::Initialize() )
	{
		return false;
	}
	return true;
}

bool ModeGame::Update()
{
	base::Update();
	_objectServer.Update(_game, *this);
	_3D_objectServer.Update(_game, *this);
	return true;
}

bool ModeGame::Draw()
{
	base::Draw();

	SetBackgroundColor(0, 0, 0);
	// 3D基本設定
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);
	SetUseBackCulling(TRUE);

	VECTOR vLightDir = VGet(-1.f, -1.f, 1.f);
	SetGlobalAmbientLight(GetColorF(0.f, 0.f, 0.f, 0.f));
	ChangeLightTypeDir(vLightDir);


	// 0(赤),0(緑),0(青)を中心に線を引く
#if _DEBUG
	{
		float linelength = 10000.f;
		VECTOR v = { 0, 0, 0 };
		DrawLine3D(VAdd(v, VGet(-linelength, 0, 0)), VAdd(v, VGet(linelength, 0, 0)), GetColor(255, 0, 0));
		DrawLine3D(VAdd(v, VGet(0, -linelength, 0)), VAdd(v, VGet(0, linelength, 0)), GetColor(0, 255, 0));
		DrawLine3D(VAdd(v, VGet(0, 0, -linelength)), VAdd(v, VGet(0, 0, linelength)), GetColor(0, 0, 255));
	}
#endif

	MV1SetScale(_handleSkySphere, VGet(2.f, 2.f, 2.f));
	MV1DrawModel(_handleSkySphere);
	_objectServer.Draw(_game, *this);
	_3D_objectServer.Draw(_game, *this);

	VECTOR ScreenPos = ConvWorldPosToScreenPos(ToDX(_vCursor));
	DrawRotaGraph(ScreenPos.x, ScreenPos.y, 0.5, 0, _cg, TRUE);

	return true;
}

