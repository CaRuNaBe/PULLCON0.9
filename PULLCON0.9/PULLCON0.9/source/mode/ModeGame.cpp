
#include "AppFrame.h"
#include "../ApplicationMain.h"
#include "ModeGame.h"
#include"../maingame/Player.h"
#include"../maingame/GameStage.h"
#include"../maingame/SkySphere.h"
#include "../maingame/SupplyEria.h"
#include"../maingame/ClearObject.h"
#include "../maingame/EnemyAAA.h"

ModeGame::ModeGame( ApplicationBase& game,int layer )
	:base( game,layer )
	,_game(game)
{
	_cg = ResourceServer::LoadGraph("res/cursor00.png");
	// 　デフォルトのフォントで、サイズ４０、太さ３のフォントを作成し
	// 作成したデータの識別番号を変数 FontHandle に保存する
	_handlefont = CreateFontToHandle(NULL, 40, 3);


	_vCursor = { 0.0f, 0.0f, 0.0f };
	_blackout = false;
	_transparence = false;
	_clear = false;



	auto stage = std::make_shared<GameStage>();
	_3D_objectServer.Add( stage );
	auto skysphere = std::make_shared<SkySphere>();
	_3D_objectServer.Add( skysphere );
	auto supplyeria = std::make_shared<SupplyEria>();
	_3D_objectServer.Add( supplyeria );
	auto clearobject = std::make_shared<ClearObject>();
	_3D_objectServer.Add( clearobject );
	auto enemyAAA = std::make_shared<EnemyAAA>();
	_3D_objectServer.Add( enemyAAA );
	auto player = std::make_shared<Player>();
	_3D_objectServer.Add( player );
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

	_3D_objectServer.Draw(_game, *this);

	if (_clear) {
		// 作成したフォントで画面左上に『CLEAR』と黄色の文字列を描画する
		DrawStringToHandle(_game.DispSizeW() / 2, _game.DispSizeH() / 2, "C L E A R!!", GetColor(255, 255, 0), _handlefont);
	}
	if (_blackout) {
		DrawBox(0, 0, _game.DispSizeW(), _game.DispSizeH(), GetColor(0, 0, 0), FALSE);
		_blackout = false;
	}

	if (!_transparence) {
		VECTOR ScreenPos = ConvWorldPosToScreenPos(ToDX(_vCursor));
		DrawRotaGraph(static_cast<int>(ScreenPos.x), static_cast<int>(ScreenPos.y), 0.5, 0, _cg, TRUE);
	}

	return true;
}

