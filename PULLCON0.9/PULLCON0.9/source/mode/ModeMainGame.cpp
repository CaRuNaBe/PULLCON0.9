/*****************************************************************//**
 * \file   ModeGame.cpp
 * \brief  ゲームモード実装
 *
 * \author 阿部健太郎
 * \date   September 2022
 *********************************************************************/

#include "ModeMainGame.h"
#include <DxLib.h>
#include "../ApplicationMain.h"
#include"../maingame/Player.h"
#include"../maingame/GameStage.h"
#include"../maingame/SkySphere.h"
#include "../maingame/SupplyEria.h"
#include"../maingame/ClearObject.h"
#include "../maingame/EnemyAAA.h"


ModeMainGame::ModeMainGame( ApplicationMain& game,int layer,std::string stagename )
	: ModeBase( game,layer )
	//,GameSclipt()
{
	const std::string FILENAME = "pullcon0.9.json";
	const std::string FILEPASS = "res/sclipt/gamesclipt/pullcon0.9.json" + FILENAME;
	const std::string GAMESCLIPT = "pullcon0.9";
	Init();
	//GameSclipt.Initialize( FILEPASS,GAMESCLIPT,FILENAME );
	
	auto player = std::make_shared<Player>();
	_3D_objectServer.Add( player );
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
	
}

ModeMainGame::~ModeMainGame()
{}
/**
 *¥fn void ModeGame::Init_modegame.
 *¥brief
 *¥return void
 */
void ModeMainGame::Init()
{
	ModeBase::Initialize();
};
/**
 *¥fn void ModeGame::Update.
 *¥brief 計算処理毎回呼ばれる
 *¥return void
 */
bool ModeMainGame::Update()
{
	ModeBase::Update();
	//GameSclipt.Update( _game,*this );
	_3D_objectServer.Update( _game,*this );
	return true;
}
/**
 *¥fn void ModeGame::Render.
 *¥brief 描画処理毎回呼ばれる
 *¥return void
 */
bool ModeMainGame::Draw()
{
	ModeBase::Draw();
  //GameSclipt.Draw(  _game,*this );
	_3D_objectServer.Draw( _game,*this );
	return true;
}
