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
#include "../maingame/StageObject.h"
#include "../maingame/EnemySpawnEria.h"
#include "../maingame/CommunicationAria.h"

namespace
{
	//ゲームコマンド
	const std::string COMMAND_STAGELABEL = "StageLabel";//ステージラベル決定コマンド
	const std::string COMMAND_JUNPLABEL = "StageJunp";//ステージジャンプコマンド
	const std::string COMMAND_CHOICE = "StageChoice";//ステージ分岐コマンド
	const std::string COMMAND_GAMESTART = "Start";//ゲームスタート
	const std::string COMMAND_END = "End";//ゲーム終了
	const std::string COMMAND_LOADING = "Load";//ロード画面表示
	const std::string COMMAND_FEEDIN = "FeedIn";//フェードイン
	const std::string COMMAND_FEEDOUT = "FeedOut";//フェードアウト
	const std::string COMMAND_TIMEWAIT = "TimeWait";//フレーム数待つ
	const std::string COMMAND_CLICK = "ClickWait";//ボタン押されるまで待つ
	const std::string COMMAND_BGM = "Bgm";//bgm再生
	const std::string COMMAND_STORY = "Story";//ストーリー再生

	const std::string COMMAND_STAGE = "Stage";//ステージ土台決定
	const std::string COMMAND_SKYSPHERE = "SkySphere";//スカイスフィア決定
	const std::string COMMAND_PLAYER = "Player";//位置決定
	const std::string COMMAND_GUNSHIP = "GunShip";//壊したらゲームクリアの位置決定
	const std::string COMMAND_ENEMYAAA = "EnemyAAA";//砲台の単品生成
	const std::string COMMAND_AREAAAA = "AreaAAA";//砲台エリア生成
	const std::string COMMAND_OBJECT = "Object";//ステージ上にオブジェクト追加
	const std::string COMMAND_AREAOBJECT = "AreaObj";//オブジェクトエリア生成
	const std::string COMMAND_ENEMYSPAWN = "AreaSpawn";//敵のスポーンエリアと敵の設定
	const std::string COMMAND_SUPPLY = "Supply";//回復エリアの生成
	const std::string COMMAND_AREACOMMUNICATION = "Communication";//会話エリア発生エリアの設定
	const std::string COMMAND_AREANOENTRY = "NoEntry";//侵入不能エリア生成



	//編集コマンド
	const std::string ECOMMAND_ADD = "add";//追加コマンド
	const std::string ECOMMAND_DELETE = "delete";//消去コマンド
	const std::string ECOMMAND_CLEAR = "clear";//初期化コマンド
	const std::string ECOMMAND_SAVE = "save";//保存コマンド
	const std::string ECOMMAND_JUNP = "jump";//編集地点変更コマンド

	//jsonファイル関係
	const std::string FILENAME = "pullcon0.9.json";//ファイル名
	const std::string FILEPASS = "res/script/gamescript/" + FILENAME;//ファイルパス
	const std::string GAMESCRIPT = "pullcon0.9";//スクリプト名
}

/**
 * \fn void ModeMainGame::ModeMainGame.
 * \brief コンストラクタ
 * \param game ApplicationMainの参照を受け取る
 * \param layer 何番目に移すか
 * \return void
 */
ModeMainGame::ModeMainGame( ApplicationMain& game,int layer )
	: ModeBase( game,layer )
{
	scripts_data = std::make_unique<ScriptsData>();
	state = ScriptState::PARSING;
#if _DEBUG
//	state = ScriptState::EDIT;
#endif
	max_line = 0;
	now_line = 0;
	feedcount = 0.0;
	Alpha = 0;
	is_notcant = false;
	is_notcommand = false;
	is_cannotdelete = false;

	Initialize( FILEPASS,GAMESCRIPT,FILENAME );

}

ModeMainGame::~ModeMainGame()
{
	Destroy();
}

void ModeMainGame::Destroy()
{
	state = ScriptState::PARSING;
	max_line = 0;
	now_line = 0;
	wait_count = 0;
	scripts_data.reset();
	scripts_data = nullptr;
}
/**
 *¥fn void ModeGame::Init_modegame.
 *¥brief
 *¥return void
 */
void ModeMainGame::Initialize( std::string jsonpath,std::string scriptsname,std::string jsonname )
{
	ModeBase::Initialize();

	if ( !scripts_data->LoadJson( jsonpath,scriptsname,jsonname ) )
	{
		return;
	}

	max_line = scripts_data->GetScriptNum();

	if ( max_line <= 0 )
	{
		state = ScriptState::EDIT;
		return;
	}

	//PreParsing();


	return;
};
/**
 *¥fn void ModeGame::Update.
 *¥brief 計算処理毎回呼ばれる
 *¥return void
 */
bool ModeMainGame::Update()
{
	ModeBase::Update();
	_3D_objectServer.Update( _game,*this );

	switch ( state )
	{
		case ScriptState::EDIT:

			break;

		case ScriptState::PREPARSING:
			PreParsing();
			break;

		case ScriptState::PARSING:
			Parsing();
			break;

		case ScriptState::GAME:
			break;

		case ScriptState::STORY:
			break;

		case ScriptState::RESULT:
			break;

		case ScriptState::CRFEEDIN:
			CrfiUpdate();
			break;

		case ScriptState::CRFEEDOUT:
			CrfoUpdate();
			break;

		case ScriptState::TIME_WAIT:
			TimeWait();
			break;

		case ScriptState::CLICK_WAIT:
			ClickWait();
			break;

		case ScriptState::LOADING:
			break;

		case ScriptState::END:
			break;
	}


	return true;
}
/**
 * @fn void ModeMainGame::CrfiUpdate ()
 * @brief スクリプトの "fi" コマンド時の計算処理
 */
void ModeMainGame::CrfiUpdate()
{
	auto i = 255 / feedcount;


	if ( Alpha > 0.0 )
	{
		Alpha -= i;
	}
	else
	{
		Alpha = 0.0;
		state = ScriptState::PARSING;
	}
}
/**
 * @fn void ModeMainGame::CrfoUpdate ()
 * @brief スクリプトの "fo" コマンド時の計算処理
 */
void ModeMainGame::CrfoUpdate()
{
	auto i = 255.0 / feedcount;


	if ( Alpha < 255.0 )
	{
		Alpha += i;
	}
	else
	{
		Alpha = 255.0;
		state = ScriptState::PARSING;
	}
}
//!
//! @fn void ModeMainGame::ClickWait()
//! @brief クリック待ち処理
//!
void ModeMainGame::ClickWait()
{
}
//!
//! @fn void ModeMainGame::TimeWait()
//! @brief 時間待ち処理
//!
void ModeMainGame::TimeWait()
{
	if ( wait_count > 0 )
	{
		--wait_count;
	}
	else
	{
		state = ScriptState::PARSING;
	}
}

bool ModeMainGame::OnCommandStageLabel( unsigned int line,const std::vector<std::string>& scripts )
{
};

bool ModeMainGame::OnCommandJunpLabel( unsigned int line,const std::vector<std::string>& scripts )
{
};

bool ModeMainGame::OnCommandChoice( unsigned int line,const std::vector<std::string>& scripts )
{
};

bool ModeMainGame::OnCommandStart( unsigned int line,const std::vector<std::string>& scripts )
{
	const size_t SCRIPTSIZE = 2;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	state = ScriptState::GAME;
	return true;
};

bool ModeMainGame::OnCommandEnd( unsigned int line,const std::vector<std::string>& scripts )
{
};

bool ModeMainGame::OnCommandLoading( unsigned int line,const std::vector<std::string>& scripts )
{
};

bool ModeMainGame::OnCommandFeedIn( unsigned int line,const std::vector<std::string>& scripts )
{
	return  true;
}

bool ModeMainGame::OnCommandFeedOut( unsigned int line,const std::vector<std::string>& scripts )
{
	return true;
}

bool ModeMainGame::OnCommandTimeWait( unsigned int line,const std::vector<std::string>& scripts )
{
};

bool ModeMainGame::OnCommandClick( unsigned int line,const std::vector<std::string>& scripts )
{
};

bool ModeMainGame::OnCommandBgm( unsigned int line,const std::vector<std::string>& scripts )
{
};

bool ModeMainGame::OnCommandStory( unsigned int line,const std::vector<std::string>& scripts )
{
};
/**
 * \fn bool ModeMainGame::OnCommandStage.
 * \brief ステージ土台配置
 * \param line 行数
 * \param scripts 文字列vector
 * \return bool
 */
bool ModeMainGame::OnCommandStage( unsigned int line,const std::vector<std::string>& scripts )
{
	const size_t SCRIPTSIZE = 2;//scriptsに入ってる文字列の最大数
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;//scripts入ってる物が指定数入っているか確認
	}
	int object_id = 0;//呼び込むステージのid
	if ( !(string::ToInt( scripts[1],object_id )) )
	{
		return false;//文字列からintに変換
	};
	auto stage = std::make_shared<GameStage>( object_id );//ステージ土台のインスタンス作成
	_3D_objectServer.Add( stage );//サーバーに追加
	return true;
};
/**
 * \fn bool ModeMainGame::OnCommandSkySphere.
 * \brief スカイスフィア配置
 * \param line
 * \param scripts
 * \return bool
 */
bool ModeMainGame::OnCommandSkySphere( unsigned int line,const std::vector<std::string>& scripts )
{
	const size_t SCRIPTSIZE = 2;//scriptsに入ってる文字列の最大数
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;//scripts入ってる物が指定数入っているか確認
	}
	int object_id = 0;//呼び込むステージのid
	if ( !(string::ToInt( scripts[1],object_id )) )
	{
		return false; // 文字列からintに変換
	};

	auto skysphere = std::make_shared<SkySphere>( object_id );//スカイスフィアのインスタンス作成
	_3D_objectServer.Add( skysphere );//サーバーに追加
	return true;
};

bool ModeMainGame::OnCommandPLayer( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	float scale = 1.0f;
	const size_t SCRIPTSIZE = 5;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[1],posi.x )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[2],posi.y )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[3],posi.z )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[4],scale )) )
	{
		return false;
	}
	if ( scale <= 0.0f )
	{
		return false;
	}
	auto player = std::make_shared<Player>();
	player->SetPosition( posi );
	player->SetScale( scale );
	_3D_objectServer.Add( player );
	return true;
};

bool ModeMainGame::OnCommandGunShip( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	float radius = 0.0f;
	const size_t SCRIPTSIZE = 4;

	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[1],posi.x )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[2],posi.y )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[3],posi.z )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[4],radius )) )
	{
		return false;
	}
	auto clearobject = std::make_shared<ClearObject>( radius );
	clearobject->SetPosition( posi );
	_3D_objectServer.Add( clearobject );
	return true;
};

bool ModeMainGame::OnCommandEnemyAAA( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	int object_min_id = 0;
	int object_max_id = 0;
	float scale = 1.0f;
	float y_rad = 0.0f;
	float x_rad = 0.0f;
	int pile_num = 0;
	int pile_min_num = 0;
	int pile_max_num = 0;
	int aim_player = 0;
	const size_t SCRIPTSIZE = 12;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[1],posi.x )) )
	{
		return false;//文字列をx座標に変換
	}
	if ( !(string::ToFloat( scripts[2],posi.y )) )
	{
		return false;//文字列をy座標に変換
	}
	if ( !(string::ToFloat( scripts[3],posi.z )) )
	{
		return false;//文字列をz座標に変換
	}
	if ( !(string::ToFloat( scripts[4],scale )) )
	{
		return false;//文字列をスケールに変換
	}
	if ( scale <= 0.0f )
	{
		return false;//scaleが0以下だったら返す
	}
	if ( !(string::ToInt( scripts[5],object_min_id )) )
	{
		return false;//砲台が生成されるときランダムに生成されるため、あらかじめ決めておいた呼び込む砲台のidの最低値
	};
	if ( !(string::ToInt( scripts[6],object_max_id )) )
	{
		return false;//砲台が生成されるときランダムに生成されるため、あらかじめ決めておいた呼び込む砲台のidの最高値
	};
	if ( !(string::ToFloat( scripts[7],y_rad )) )
	{
		return false;//y軸砲台の傾きの初期位置
	}
	if ( !(string::ToFloat( scripts[8],x_rad )) )
	{
		return false;//z軸砲台の傾きの初期位置
	}
	if ( !(string::ToInt( scripts[9],pile_min_num )) )
	{
		return false;//下に重なる砲台の個数の最低値
	}
	if ( !(string::ToInt( scripts[10],pile_max_num )) )
	{
		return false;//下に重なる砲台の個数の最高値
	}
	pile_num = utility::get_random( pile_min_num,pile_max_num );//ランダム値取得
	if ( !(string::ToInt( scripts[11],aim_player )) )
	{
		return false;
	}
	auto enemyAAA = std::make_shared<EnemyAAA>( object_min_id,object_max_id,pile_num );
	enemyAAA->SetPosition( posi );
	enemyAAA->SetScale( scale );
	enemyAAA->SetAxialX( x_rad );
	enemyAAA->SetAxialY( y_rad );
	enemyAAA->SetAim( aim_player );
	_3D_objectServer.Add( enemyAAA );
	return true;
};

bool ModeMainGame::OnCommandAreaAAA( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	const size_t SCRIPTSIZE = 14;
	float range = 0.0f;
	float scale = 1.0f;
	float interval = 0.0f;
	int object_min_id = 0;
	int object_max_id = 0;
	int pile_num = 0;
	int pile_min_num = 0;
	int pile_max_num = 0;
	int min_map_draw_red = 0;
	int min_map_draw_green = 0;
	int min_map_draw_blue = 0;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[1],posi.x )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[2],posi.y )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[3],posi.z )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[4],scale )) )
	{
		return false;
	}
	if ( scale <= 0.0f )
	{
		return false;
	}
	if ( !(string::ToInt( scripts[5],object_min_id )) )
	{
		return false;//文字列からintに変換
	};
	if ( !(string::ToInt( scripts[6],object_max_id )) )
	{
		return false;//文字列からintに変換
	};
	if ( !(string::ToFloat( scripts[7],range )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[8],interval )) )
	{
		return false;
	}

	if ( !(string::ToInt( scripts[9],pile_min_num )) )
	{
		return false;
	}
	if ( !(string::ToInt( scripts[10],pile_max_num )) )
	{
		return false;
	}
	pile_num = utility::get_random( pile_min_num,pile_max_num );

	if ( !(string::ToInt( scripts[11],min_map_draw_red )) )
	{
		return false;
	}
	if ( !(string::ToInt( scripts[12],min_map_draw_green )) )
	{
		return false;
	}
	if ( !(string::ToInt( scripts[13],min_map_draw_blue )) )
	{
		return false;
	}
	auto color = GetColor( min_map_draw_red,min_map_draw_green,min_map_draw_blue );
	/*
	std::vector<math::vector4>posivec;
	while ( true )
	{
		posix = utility::get_random(0,);
		posi.x; posi.z;


		if ( posivec.size()>1000 )
		{
			break;
		}
		if ( < range )
		{
			continue;
		}
		vector4 setposi{,posi.y,};
		posivec.push_back( setposi );
	}
	*/
	auto enemyAAA = std::make_shared<EnemyAAA>( object_min_id,object_max_id,pile_num );
	enemyAAA->SetPosition( posi );
	enemyAAA->SetScale( scale );
	_3D_objectServer.Add( enemyAAA );

	return true;
};

bool ModeMainGame::OnCommandObject( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	float scale = 1.0f;
	int object_id = 0;
	int collision_id = 1;
	const size_t SCRIPTSIZE = 7;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[1],posi.x )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[2],posi.y )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[3],posi.z )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[4],scale )) )
	{
		return false;
	}
	if ( scale <= 0.0f )
	{
		return false;
	}
	if ( !(string::ToInt( scripts[5],object_id )) )
	{
		return false;//文字列からintに変換
	};
	if ( !(string::ToInt( scripts[6],collision_id )) )
	{
		return false;//文字列からintに変換
	};
	auto object = std::make_shared<StageObject>( object_id,collision_id );
	object->SetPosition( posi );
	object->SetScale( scale );
	_3D_objectServer.Add( object );
	return true;
};

bool ModeMainGame::OnCommandAreaObj( unsigned int line,const std::vector<std::string>& scripts )
{
	return true;
};

bool ModeMainGame::OnCommandAreaSpawn( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	int spawn_id = 0;
	int spawn_fream = 0;
	const size_t SCRIPTSIZE = 6;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[1],posi.x )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[2],posi.y )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[3],posi.z )) )
	{
		return false;
	}
	if ( !(string::ToInt( scripts[4],spawn_fream )) )
	{
		return false;//文字列からintに変換
	};
	if ( !(string::ToInt( scripts[5],spawn_id )) )
	{
		return false;//文字列からintに変換
	};
	auto spawn_eria = std::make_shared<EnemySpawnEria>( spawn_fream,spawn_id );
	spawn_eria->SetPosition( posi );
	_3D_objectServer.Add( spawn_eria );
	return true;
};

bool ModeMainGame::OnCommandSupply( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	float radius = 0.0f;
	const size_t SCRIPTSIZE = 5;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[1],posi.x )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[2],posi.y )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[3],posi.z )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[4],radius )) )
	{
		return false;
	}
	auto supplyeria = std::make_shared<SupplyEria>( radius );
	supplyeria->SetPosition( posi );
	_3D_objectServer.Add( supplyeria );
	return true;
};

bool ModeMainGame::OnCommandCommunication( unsigned int line,const std::vector<std::string>& scripts )
{
	vector4 posi;
	float radius = 0.0f;

	const size_t SCRIPTSIZE = 6;
	if ( scripts.size() != SCRIPTSIZE )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[1],posi.x )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[2],posi.y )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[3],posi.z )) )
	{
		return false;
	}
	if ( !(string::ToFloat( scripts[4],radius )) )
	{
		return false;
	}
	std::string story_name = scripts[5];
	auto commu_aria = std::make_shared<CommunicationAria>( radius,story_name );
	commu_aria->SetPosition( posi );
	_3D_objectServer.Add( commu_aria );
	return true;
};

bool ModeMainGame::OnCommandNoEntry( unsigned int line,const std::vector<std::string>& scripts )
{

	return true;
};

void ModeMainGame::Edit()
{
	int None = 0;
	if ( (state == ScriptState::EDIT) && (CheckHitKey( KEY_INPUT_RETURN ) == 1) )
	{
		FunctionEditCommand editCommand;//文字列でのスイッチ文
		editCommand.insert( std::make_pair( ECOMMAND_ADD,&ModeMainGame::OnEditCommandAdd ) );
		editCommand.insert( std::make_pair( ECOMMAND_DELETE,&ModeMainGame::OnEditCommandDelete ) );
		editCommand.insert( std::make_pair( ECOMMAND_CLEAR,&ModeMainGame::OnEditCommandClear ) );
		editCommand.insert( std::make_pair( ECOMMAND_JUNP,&ModeMainGame::OnEditCommandSave ) );
		editCommand.insert( std::make_pair( ECOMMAND_SAVE,&ModeMainGame::OnEditCommandJunp ) );

		int x = 0; int y = 0;
		std::string buf = "";
		auto cchar = const_cast<char*>(buf.c_str());
		DrawString( x,y,"コマンドを入力してください\nESCで戻る\nadd:オブジェクトの追加\ndelete:オブジェクトの消去\nclear:いま追加されているゲームコマンドを初期化コマンド\njump:編集地点変更\nsave:ファイルに書き込み",GetColor( 255,255,255 ) );
		if ( is_notcant )
		{
			is_notcant = false;
			DrawString( x,150,"追加できませんでした\n",GetColor( 255,255,255 ) );
		}
		if ( is_notcommand )
		{
			is_notcommand = false;
			DrawString( x,200,"そのようなコマンドはありません\n",GetColor( 255,255,255 ) );
		}
		if ( is_cannotdelete )
		{
			is_cannotdelete = false;
			DrawString( x,250,"消去出来ませんでした\n",GetColor( 255,255,255 ) );
		}
		if ( KeyInputSingleCharString( 0,500,10,cchar,TRUE ) == 1 )
		{
			std::string ecommandbuf = cchar;
			ClearDrawScreen();
			if ( editCommand.count( ecommandbuf ) <= None )
			{
				is_notcommand = true;
				return;
			}

			(this->*editCommand[ecommandbuf])();

		}
		else
		{
			now_line = 0;
			max_line = scripts_data->GetScriptNum();
			state = ScriptState::PARSING;
		};
	}
}

bool ModeMainGame::OnEditCommandAdd()
{
	int x,y;
	x = y = 0;
	std::string buf;
	auto cchar = const_cast<char*>(buf.c_str());
	DrawString( x,y,"何を追加しますか\n追加できるもの",GetColor( 255,255,255 ) );

	if ( KeyInputSingleCharString( 0,500,100,cchar,TRUE ) == 1 )
	{
		std::string ecommandbuf = cchar;

		if ( CheckInputString( ecommandbuf ) )
		{
			scripts_data->ScriptAdd( ecommandbuf );
		}
		else
		{
			ClearDrawScreen();
			is_notcant = true;
		}
	}
	return true;
};
bool ModeMainGame::OnEditCommandDelete()
{
	int x,y;
	x = y = 0;
	std::string buf = "";
	auto cchar = const_cast<char*>(buf.c_str());
	DrawString( x,y,"何を消去しますか\n番号を入力してください",GetColor( 255,255,255 ) );
	y += 30;
	auto maxline = scripts_data->GetScriptNum();
	for ( unsigned int i = 0; i <= maxline; i++ )
	{
		auto script = scripts_data->GetScriptLine( i );
		auto stringnew = "番号%d" + script;
		DrawFormatString( x,y,GetColor( 255,255,255 ),stringnew.c_str(),i + 1 );
		y += 30;
	}
	if ( KeyInputSingleCharString( 0,500,30,cchar,TRUE ) == 1 )
	{
		int deliteLine = 0;
		std::string ecommandbuf = cchar;
		string::ToInt( ecommandbuf,deliteLine );
		deliteLine--;
		if ( deliteLine < 0 )
		{
			is_cannotdelete = true;
			return false;
		}
		scripts_data->ScriptDelete( deliteLine );
	}
	return true;
};
bool ModeMainGame::OnEditCommandClear()
{
	scripts_data->ScriptClear();
	return true;
};
bool ModeMainGame::OnEditCommandSave()
{
	scripts_data->WriteJson( FILENAME,GAMESCRIPT );
	return true;
};
bool ModeMainGame::OnEditCommandJunp()
{
	return true;
};

bool ModeMainGame::CheckInputString( std::string command )
{
	auto script = string::Split( command,"," );

	FunctionGameCommand comand_funcs;
	comand_funcs.insert( std::make_pair( COMMAND_PLAYER,&ModeMainGame::OnCommandPLayer ) );
	comand_funcs.insert( std::make_pair( COMMAND_STAGE,&ModeMainGame::OnCommandStage ) );
	comand_funcs.insert( std::make_pair( COMMAND_SKYSPHERE,&ModeMainGame::OnCommandSkySphere ) );
	comand_funcs.insert( std::make_pair( COMMAND_GUNSHIP,&ModeMainGame::OnCommandGunShip ) );
	comand_funcs.insert( std::make_pair( COMMAND_SUPPLY,&ModeMainGame::OnCommandSupply ) );
	comand_funcs.insert( std::make_pair( COMMAND_ENEMYAAA,&ModeMainGame::OnCommandEnemyAAA ) );
	comand_funcs.insert( std::make_pair( COMMAND_AREAAAA,&ModeMainGame::OnCommandEnemyAAA ) );
	comand_funcs.insert( std::make_pair( COMMAND_GAMESTART,&ModeMainGame::OnCommandStart ) );
	//comand_funcs.insert( std::make_pair( COMMAND_FEEDIN,&ModeMainGame::OnCommandCrfi ) );
	//comand_funcs.insert( std::make_pair( COMMAND_FEEDOUT,&ModeMainGame::OnCommandCrfo ) );
	if ( command.size() <= 0 )
	{
		return false;
	}

	if ( comand_funcs.count( script[0] ) <= 0 )
	{
		return false;
	}

	if ( !(this->*comand_funcs[script[0]])(now_line,script) )
	{
		return false;
	};
	state = ScriptState::EDIT;
	_3D_objectServer.Clear();
	return true;
}

void ModeMainGame::PreParsing()
{
}

void ModeMainGame::Parsing()
{
	auto stop_parsing = false;
	unsigned	int dateempty = 0;
	FunctionGameCommand comand_funcs;
	comand_funcs.insert( std::make_pair( COMMAND_PLAYER,&ModeMainGame::OnCommandPLayer ) );
	comand_funcs.insert( std::make_pair( COMMAND_STAGE,&ModeMainGame::OnCommandStage ) );
	comand_funcs.insert( std::make_pair( COMMAND_SKYSPHERE,&ModeMainGame::OnCommandSkySphere ) );
	comand_funcs.insert( std::make_pair( COMMAND_GUNSHIP,&ModeMainGame::OnCommandGunShip ) );
	comand_funcs.insert( std::make_pair( COMMAND_SUPPLY,&ModeMainGame::OnCommandSupply ) );
	comand_funcs.insert( std::make_pair( COMMAND_ENEMYAAA,&ModeMainGame::OnCommandEnemyAAA ) );
	comand_funcs.insert( std::make_pair( COMMAND_AREAAAA,&ModeMainGame::OnCommandAreaAAA ) );
	comand_funcs.insert( std::make_pair( COMMAND_GAMESTART,&ModeMainGame::OnCommandStart ) );
	//comand_funcs.insert( std::make_pair( COMMAND_FEEDIN,&ModeMainGame::OnCommandCrfi ) );
	//comand_funcs.insert( std::make_pair( COMMAND_FEEDOUT,&ModeMainGame::OnCommandCrfo ) );
	//comand_funcs.insert( std::make_pair( COMMAND_VE,&ModeMainGame::OnCommandPlayanime ) );
	//comand_funcs.insert( std::make_pair( COMMAND_E,&ModeMainGame::OnCommandScliptend ) );

	while ( !stop_parsing && (now_line >= 0) && (now_line < max_line) )
	{
		const auto script = scripts_data->GetScript( now_line );
		const auto command = (script[0]);
		std::string string_comand{command};
		/*
		bool isThrough = false;

		isThrough = (string_comand == COMMAND_I);
		if ( isThrough == false )
		{
			isThrough = string_comand == COMMAND_IM;
		}

		if ( !isThrough )
		{
			if ( string_comand == COMMAND_W || string_comand == COMMAND_FI || string_comand == COMMAND_FO || string_comand == COMMAND_VE )
			{
				stop_parsing = (this->*comand_funcs[string_comand])(now_line,script);
			}
			else
			{
				(this->*comand_funcs[string_comand])(now_line,script);
			}

			if ( string_comand == COMMAND_A || string_comand == COMMAND_E )
			{
				stop_parsing = true;
			}
		}
		*/
		(this->*comand_funcs[string_comand])(now_line,script);
		if ( string_comand == COMMAND_GAMESTART )
		{
			stop_parsing = true;
			state = ScriptState::GAME;
		}
		++now_line;
	}
	if ( max_line <= dateempty )
	{
		state = ScriptState::EDIT;
	}
}
/**
 *¥fn void ModeGame::Render.
 *¥brief 描画処理毎回呼ばれる
 *¥return void
 */
bool ModeMainGame::Draw()
{
	ModeBase::Draw();
	DrawFormatString( 1000,0,GetColor( 255,255,255 ),"State%d",state );
	_3D_objectServer.Draw( _game,*this );
	switch ( state )
	{
		case ScriptState::EDIT:
			Edit();
			break;

		case ScriptState::PREPARSING:

			break;

		case ScriptState::PARSING:

			break;

		case ScriptState::GAME:
			break;

		case ScriptState::STORY:
			break;

		case ScriptState::RESULT:
			break;

		case ScriptState::CRFEEDIN:
			//DrawFeedin(_game);
			break;

		case ScriptState::CRFEEDOUT:
			//DrawFeedout(_game);
			break;

		case ScriptState::LOADING:
			break;

		case ScriptState::END:
			break;
	}


	return true;
}
/**
 *¥fn void script_engine::DrawFeedin.
 *¥brief "fi" コマンドによる描画
 *¥return void
 */
/*
void ModeMainGame::DrawFeedin( ApplicationBase& game )const
{
	for ( auto&& crfi : crfi_list )
	{
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,static_cast<int>(_Alpha) );
		DrawBox( 0,0,game.DispSizeW(),game.DispSizeH(),GetColor( crfi->GetRed(),crfi->GetGreen(),crfi->GetBlue() ),TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}
}
*/
/**
 *¥fn void script_engine::DrawFeedout.
 *¥brief "fo" コマンドによる描画
 *¥return void
 */
/*
void ModeMainGame::DrawFeedout( ApplicationBase& game )const
{
	for ( auto&& crfo : crfo_list )
	{
		auto color = GetColor( crfo->GetRed(),crfo->GetGreen(),crfo->GetBlue() );
		auto a = static_cast<int>(_Alpha);
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,a );
		DrawBox( 0,0,game.DispSizeW(),game.DispSizeH(),color,TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}
}
*/