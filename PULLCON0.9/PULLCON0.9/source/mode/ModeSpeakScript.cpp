﻿/*****************************************************************//**
 * @file   ModeSpeakScript.cpp
 * @brief  会話用スクリプト
 *
 * @author 阿部健太郎
 * @date   February 2023
 *********************************************************************/
/*コマンド一覧
///////////// いま1フレーム1/60秒なので60となると１秒になります//////////////////
////////////今の画面設定は1920＊1080なので一番左上の座標が（0,0）一番右下が（1920,1080）になります//////////
/// 呼び込みはスクリプト一番最初に書いてくださいうまく動かない場合があります//
/// パスを入力するとき./resourcefile/を書いてからファイル名を書いてくださいうまく呼び込めません///
画像、動画呼び込み
"i,画像名,画像パス",
※例："i,テキストボックス,./resourcefile/text_box.png",
音系呼び込み
"im,音名,音パス",
※例："im,決定音,./resourcefile/se/yes_effect.mp3",
カラーフェードイン
"fi, フレーム数,赤の色段階,緑の色段階,青の色段階",
※例："fi,120,255,0,0",こうすると画面が2秒かけてだんだん赤くなって行きます
カラーフェードアウト
"fo, フレーム数,赤の色段階,緑の色段階,青の色段階",
※例："fo,60,0,0,0",こうすると画面が1秒かけて画面が黒から透明になって行きます
画像フェードイン
"di,描画する順番,ｘ座標,ｙ座標,フレーム数,画像名",
※例："di,0,0,0,60,テキストボックス",こうすると画面座標（0,0）レイヤー１番目の所に1秒かけて出現します逆に0にするといきなり出現します
画像フェードアウト
"do,描画する順番,x座標,y座標,フレーム数,画像名",
※例："di,2,60,60,120,テキストボックス",こうすると画面座標（60,60）レイヤー3番目の所に2秒かけて消えます逆に0にするといきなり消えます。
またdiコマンドで登録した画像を全消去します
セリフ
"m,誰がしゃべるか,セリフ",
※例："m,イーリス,セリフ",こうするとイーリスがしゃべった感じになります逆に名前がない場合の表記も可能です
入力待ち
"＠",
aボタン押すまで待ちます。押した場合決定音がなります
待つ
"w, フレーム数",
※例："w, 300",こうすると5秒止まってから次に進みます
ループ再生//bgmに使用
"bg,音名",
※例："bg,決定音",決定音が無限ループします音を止めるまでずっとなります
一回再生//キャラがしゃべる時や効果音に使用
"fg,音名",
※例："fg,決定音",決定音が一回再生します
音を止める//bgmを止めたいときに使用
"gs,音名",
音を止めます
ムービー再生//
"ve,画像名",
※例："ve,オープニング",オープニングが再生します。終わるかスタートボタンをおしたとき次に進みます
コマンド終了//
"e",
スクリプトが終わるとき使用
*/

#include "ModeSpeakScript.h"
#include <algorithm>
#include <utility>
#include <stdio.h>

namespace
{
// スクリプト コマンド
	std::string COMMAND_I = "i";
	std::string COMMAND_IM = "im";
	std::string COMMAND_FI = "fi";
	std::string COMMAND_FO = "fo";
	std::string COMMAND_DI = "di";
	std::string COMMAND_DO = "do";
	std::string COMMAND_M = "m";
	std::string COMMAND_A = "@";
	std::string COMMAND_W = "w";
	std::string COMMAND_BG = "bg";
	std::string COMMAND_FG = "fg";
	std::string COMMAND_GS = "gs";
	std::string COMMAND_VE = "ve";
	std::string COMMAND_E = "e";

//文字設定
	constexpr auto FONT_SIZE = 34;

	constexpr auto SPEAK_SKIP = 30;
	constexpr auto MSG_WORD_MAX = 100;

	constexpr auto MSG_LINE_MAX = 3;
	constexpr auto MSG_LINE_WIDTH = MSG_WORD_MAX * FONT_SIZE;
	constexpr auto MSG_LINE_HEIGHT = 35;
	constexpr auto MSG_LINE_GAP_HEIGHT = 15;
	constexpr auto MSG_LINE_GRID_HEIGHT = MSG_LINE_HEIGHT + MSG_LINE_GAP_HEIGHT;

	constexpr auto MSG_SPEAKER_SET_X = 360;
	constexpr auto MSG_SPEAKER_SET_Y = 790;

	constexpr auto MSG_SET_X = MSG_SPEAKER_SET_X + (FONT_SIZE / 2);
	constexpr auto MSG_SET_Y = MSG_SPEAKER_SET_Y + FONT_SIZE + 10;

	//メッセージウィンドウ設定
	constexpr auto MSG_WINDOW_WIDTH = 1480;
	constexpr auto MSG_WINDOW_HEIGHT = 270;

	constexpr auto MSG_WINDOW_LEFT = 255;
	constexpr auto MSG_WINDOW_RIGHT = MSG_WINDOW_LEFT + MSG_WINDOW_WIDTH;
	constexpr auto MSG_WINDOW_TOP = 755;
	constexpr auto MSG_WINDOW_BOTTOM = MSG_WINDOW_TOP + MSG_WINDOW_HEIGHT;

	//名前の下のライン表示定数
	constexpr auto LINE_THICKNESS = 5;
	constexpr auto LINE_POSITION_LEFT = MSG_SPEAKER_SET_X;
	constexpr auto LINE_POSITION_TOP = MSG_SPEAKER_SET_Y + FONT_SIZE;
	constexpr auto LINE_POSITION_BOTTOM = LINE_POSITION_TOP + LINE_THICKNESS;

	//クリック待ち画像のポジション
	constexpr auto CLICK_WAIT_X = 1600;
	constexpr auto CLICK_WAIT_Y = 900;

	//スキップ設定
	constexpr auto SCRIPT_SKIP_TIME = 200;
	constexpr auto ANIME_SKIP_OK_TIME = 120;

		// 一度計算したら固定値な物
	int screen_width = 1920;
	int screen_height = 1080;

	int screen_center_x = screen_width / 2;
	int screen_center_y = screen_height / 2;

	unsigned int message_string_color = 0;
	//script用ファイルパス
	std::string FILE_PASS = "res/script/";
	std::string FILE_NAME = ".json";
		//文字列分割用
	const std::string DELIMITER = ",";
}

ModeSpeakScript::ModeSpeakScript( ApplicationBase& game,int layer,std::string storyname )
	:ModeBase( game,layer )
{
	auto character_story = string::Split( storyname,"/" );
	FILE_PASS += character_story[0];
	FILE_NAME = character_story[1] + FILE_NAME;
	FILE_PASS += FILE_NAME;
	Initialize( FILE_PASS,character_story[1],FILE_NAME );
	InitializeStrings();
}

ModeSpeakScript::~ModeSpeakScript()
{
	Destroy();
}

void ModeSpeakScript::Initialize( std::string jsonpath,std::string scriptsname,std::string jsonname )
{
	movie_play.reset();

	scripts_data.reset();
	scripts_data = std::make_unique<ScriptsData>();
	scripts_data->LoadJson( jsonpath,scriptsname,jsonname );

	max_line = scripts_data->GetScriptNum();
	state = ScriptState::PREPARSING;
	feedcount = 0.0;
	_Alpha = 0;
	now_line = 0;
	wait_count = 0;
	Speak_skip_count = 0;
	Script_skip_count = 0;
	Anime_count = 0;
	Hide_point = 255;
	is_Skip_ok = false;
	is_click_wait_visible = false;
	is_message_output = false;
	is_finishdraw = false;
	is_hide = false;
	is_amime_skip = false;
};
//!
//! @fn bool ScriptEngine::InitializeStrings()
//! @brief スクリプトエンジン用文字列描画の初期化
//! @return 処理の成否
//!
bool ModeSpeakScript::InitializeStrings()
{
	SetFontSize( FONT_SIZE );

	auto screen_depth = 0;

	if ( GetScreenState( &screen_width,&screen_height,&screen_depth ) != 0 )
	{
		return false;
	}
	is_Click_on = false;
	message_string_color = GetColor( 0,0,0 );

	return true;
}

//!
//! @fn void ScriptEngine::Destroy()
//! @brief 明示的なスクリプトエンジンの終了処理
//! @details 無理に呼び出す必要はありませんが
//! インスタンスを再利用したい場合などに呼び出します。
//!
void ModeSpeakScript::Destroy()
{
	movie_play.reset();
	scripts_data.reset();
	scripts_data = nullptr;

	state = ScriptState::PREPARSING;
	max_line = 0;
	now_line = 0;
	wait_count = 0;

	is_click_wait_visible = false;
	is_message_output = false;
	is_Skip_ok = false;

	image_list.clear();
	se_list.clear();
	crfi_list.clear();
	crfo_list.clear();
	drawin_list.clear();
	drawout_list.clear();
}

//!
//! @fn void ScriptEngine::Update()
//! @brief スクリプトエンジンの更新処理
//! @details 毎フレーム呼び出す必要があります。
//!
bool ModeSpeakScript::Update()
{
	auto is_update_message = false;

	switch ( state )
	{
		case ScriptState::PREPARSING:
			PreParsing();
			break;

		case ScriptState::PARSING:
			Parsing();
			break;

		case ScriptState::CRFEEDIN:
			CrfiUpdate();
			is_update_message = true;
			break;

		case ScriptState::PLAY_ANIME:
			PlayUpdate();
			break;

		case ScriptState::CRFEEDOUT:
			CrfoUpdate();
			is_update_message = true;
			break;

		case ScriptState::TIME_WAIT:
			TimeWait();
			is_update_message = true;
			break;

		case ScriptState::CLICK_WAIT:
			ClickWait();
			is_update_message = true;
			break;
		case ScriptState::SCRIPT_END:
			//_game.isEndsclipt = true;
			break;
	}

	feed_draw();

	if ( is_Skip_ok )
	{
		Speak_skip();
		Script_skip();
		Hide_Message();
	}


	if ( is_update_message )
	{
		UpdateMessage();
	}
	return true;
}

//!
//! @fn void ScriptEngine::UpdateMessage()
//! @brief 文字列を 1 文字づつ表示させる処理
//!
void ModeSpeakScript::UpdateMessage()
{
	is_click_wait_visible = false;

	for ( auto&& message : message_list )
	{
		const auto& area = message->GetArea();
		const auto right_goal = message->GetRightGoal();

		// クリックされたら全メッセージを表示
		if ( _game.Getinput().XinputEveryOtherKey( XINPUT_BUTTON_A,20 ) )
		{
			message->UpdateAreaRight( right_goal );
			continue;
		}

		// 右終端(全文字列)になるまで 1 文字サイズ分づつ足して行く
		if ( area.rightBottom.x < right_goal )
		{
			message->UpdateAreaRight( static_cast <int>(area.rightBottom.x) + (FONT_SIZE / 2) );
			return; // 1 文字分処理したらメソッド終了
		}
	}

	// return せずに for 文が終わったなら全文字列を表示している
	is_message_output = false;

	if ( state == ScriptState::CLICK_WAIT )
	{
		is_click_wait_visible = true;
	}
}

/**
 *¥fn void script_engine.cpp::PreParsing.
 * @brief スクリプトの事前解析
 * im' コマンド(ラベル)と 'i' コマンド(イメージ)を
 * 予め全て処理してリスト化します。
 *¥return void
 */
void ModeSpeakScript::PreParsing()
{
	funcs_type comand_funcs;
	comand_funcs.insert( std::make_pair( COMMAND_I,&ModeSpeakScript::OnCommandImage ) );
	comand_funcs.insert( std::make_pair( COMMAND_IM,&ModeSpeakScript::OnCommandSe ) );

	const auto script = scripts_data->GetScript( now_line,DELIMITER );
	const auto& char_command = (script[0]);
	std::string string_comand{char_command};

	if ( string_comand == COMMAND_IM || string_comand == COMMAND_I )
	{
		(this->*comand_funcs[string_comand])(now_line,script);
	}

	now_line++;

	if ( now_line >= max_line )
	{
		//_game.isLoadend = true;
		now_line = 0;
		is_Skip_ok = true;
		state = ScriptState::PARSING;
	}
}

//!
//! @fn void ScriptEngine::Parsing()
//! @brief スクリプトの解析
//! @details スクリプトを 1 行単位で処理します。
//! (インタープリタ方式)
//!
void ModeSpeakScript::Parsing()
{
	is_hide = false;
	is_finishdraw = false;
	Hide_point = 255;
	message_list.clear();
	movie_play.reset();
	auto stop_parsing = false;
	funcs_type comand_funcs;
	comand_funcs.insert( std::make_pair( COMMAND_FI,&ModeSpeakScript::OnCommandCrfi ) );
	comand_funcs.insert( std::make_pair( COMMAND_FO,&ModeSpeakScript::OnCommandCrfo ) );
	comand_funcs.insert( std::make_pair( COMMAND_DI,&ModeSpeakScript::OnCommandDrawin ) );
	comand_funcs.insert( std::make_pair( COMMAND_DO,&ModeSpeakScript::OnCommandDrawout ) );
	comand_funcs.insert( std::make_pair( COMMAND_M,&ModeSpeakScript::OnCommandMessage ) );
	comand_funcs.insert( std::make_pair( COMMAND_A,&ModeSpeakScript::OnCommandClick ) );
	comand_funcs.insert( std::make_pair( COMMAND_W,&ModeSpeakScript::OnCommandWait ) );
	comand_funcs.insert( std::make_pair( COMMAND_BG,&ModeSpeakScript::OnCommandMusicloop ) );
	comand_funcs.insert( std::make_pair( COMMAND_FG,&ModeSpeakScript::OnCommandMusicbag ) );
	comand_funcs.insert( std::make_pair( COMMAND_GS,&ModeSpeakScript::OnCommandMusicstop ) );
	comand_funcs.insert( std::make_pair( COMMAND_VE,&ModeSpeakScript::OnCommandPlayanime ) );
	comand_funcs.insert( std::make_pair( COMMAND_E,&ModeSpeakScript::OnCommandScriptend ) );

	while ( !stop_parsing && (now_line >= 0) && (now_line < max_line) )
	{
		const auto script = scripts_data->GetScript( now_line,DELIMITER );
		const auto& command = (script[0]);
		std::string string_comand{command};

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
		++now_line;
	}
}

/**
 * @fn void  ScriptEngine::feed_draw ().
 * @brief di doコマンド計算処理
 */
void  ModeSpeakScript::feed_draw()
{
	for ( auto&& drawin : drawin_list )
	{
		if ( !(drawin->GetDrawcomplete()) )
		{
			auto i = 255.0 / drawin->GetinCount();

			drawin->SetDrawAlphain( drawin->GetDrawAlphain() + i );

			if ( drawin->GetDrawAlphain() >= 255.0 )
			{
				drawin->SetDrawAlphain( 255.0 );
				drawin->SetDrawcomplete( true );
			}
		}
	}

	for ( auto&& drawout : drawout_list )
	{
		if ( !(drawout->GetDrawcomplete()) )
		{
			auto i = 255.0 / drawout->GetoutCount();

			drawout->SetDrawAlphaout( drawout->GetDrawAlphaout() - i );

			if ( drawout->GetDrawAlphaout() <= 0.0 )
			{
				drawout->SetDrawAlphaout( 0.0 );
				drawout->SetDrawcomplete( true );
			}
		}
	}

	for ( auto&& drawin : drawin_list )
	{
		if ( !(drawin->GetDrawcomplete()) )
		{
			return;
		}
	}

	for ( auto&& drawout : drawout_list )
	{
		if ( !(drawout->GetDrawcomplete()) )
		{
			return;
		}
	}

	is_finishdraw = true;
};

/**
 *¥fn void script_engine.cpp::Speakskip.
 *¥brief 会話をスキップする
 *¥return void
 */
void  ModeSpeakScript::Speak_skip()
{
	if ( _game.Getinput().GetTrgXinput( XINPUT_BUTTON_A ) )
	{
		Speak_skip_count++;
		if ( 0 == Speak_skip_count % SPEAK_SKIP )
		{
			is_Click_on = true;
		}
		else
		{
			is_Click_on = false;
		}
	}
	else
	{
		is_Click_on = false;
		Speak_skip_count = 0;
	}
};

/**
 *¥fn void script_engine.cpp::Scriptskip.
 *¥brief スクリプト自体をスキップする
 *¥return void
 */
void ModeSpeakScript::Script_skip()
{
	if ( _game.Getinput().GetTrgXinput( XINPUT_BUTTON_Y ) )
	{
		Script_skip_count++;
		if ( Script_skip_count > SCRIPT_SKIP_TIME )
		{
			if ( state == ScriptState::PLAY_ANIME )
			{
				PauseMovieToGraph( movie_play->GetMvHandle() );
			}
			for ( auto&& se : se_list )
			{
				StopSoundMem( se->GetHandle() );
			}
			state = ScriptState::SCRIPT_END;
		}
	}
	else
	{
		Script_skip_count = 0;
	}
};

/**
 *¥fn void script_engine::Hide_Message.
 *¥brief
 *¥return void
 */
void ModeSpeakScript::Hide_Message()
{
	if ( (_game.Getinput().GetTrgXinput( XINPUT_BUTTON_B )) && is_hide )
	{
		is_hide = false;
		Hide_point = 255;
	}
	else if ( (_game.Getinput().GetTrgXinput( XINPUT_BUTTON_B )) && !is_hide )
	{
		is_hide = true;
		Hide_point = 0;
	}
};

/**
 * @fn void ScriptEngine::CrfiUpdate ()
 * @brief スクリプトの "fi" コマンド時の計算処理
 */
void ModeSpeakScript::CrfiUpdate()
{
	auto i = 255 / feedcount;

	if ( is_message_output )
	{
		return;
	}
	if ( _Alpha > 0.0 )
	{
		_Alpha -= i;
	}
	else
	{
		_Alpha = 0.0;
		state = ScriptState::PARSING;
	}
}

/**
 * @fn void ScriptEngine::CrfoUpdate ()
 * @brief スクリプトの "fo" コマンド時の計算処理
 */
void ModeSpeakScript::CrfoUpdate()
{
	auto i = 255.0 / feedcount;

	if ( is_message_output )
	{
		return;
	}
	if ( _Alpha < 255.0 )
	{
		_Alpha += i;
	}
	else
	{
		_Alpha = 255.0;
		state = ScriptState::PARSING;
	}
}

//!
//! @fn void ScriptEngine::ClickWait()
//! @brief クリック待ち処理
//!
void ModeSpeakScript::ClickWait()
{
	if ( is_message_output )
	{
		return;
	}
	if ( is_finishdraw )
	{
		if ( _game.Getinput().XinputEveryOtherKey( XINPUT_BUTTON_A,2 ) )
		{
			is_finishdraw = false;
			state = ScriptState::PARSING;
		}
	}
}

//!
//! @fn void ScriptEngine::TimeWait()
//! @brief 時間待ち処理
//!
void ModeSpeakScript::TimeWait()
{
	if ( is_message_output )
	{
		return;
	}
	if ( wait_count > 0 )
	{
		--wait_count;
	}
	else
	{
		if ( is_finishdraw )
		{
			is_finishdraw = false;
			state = ScriptState::PARSING;
		}
	}
}

/**
 *@fn void ScriptEngine::Playprocess ().
 * @brief アニメ再生中処理
 */
void ModeSpeakScript::PlayUpdate()
{
	Anime_count++;
	if ( Anime_count > ANIME_SKIP_OK_TIME )
	{
		is_amime_skip = true;
	}
	if ( is_amime_skip && (_game.Getinput().GetTrgXinput( XINPUT_BUTTON_A ) || (GetMovieStateToGraph( movie_play->GetMvHandle() ) == 0)) )
	{
		is_amime_skip = false;
		Anime_count = 0;
		PauseMovieToGraph( movie_play->GetMvHandle() );
		state = ScriptState::PARSING;
	}
};

//!
//! @fn bool ScriptEngine::CalculateMessageArea(const std::string& message, Rect& area, int& right_goal)
//! @brief メッセージ文字列より表示エリアや右終端を計算する
//! @param[in] message メッセージ文字列
//! @param[out] area メッセージ表示エリア
//! @param[out] right_goal メッセージ右終端
//! @return 処理の成否
//! @details メッセージの順番や文字数より表示エリアを計算します。
//! 表示エリアの右側は、初期値は左側と同値とします。
//! (数学的にはエリアは面積を持たない)
//! これは左側から 1 文字づつ表示していく仕様の為です。
//! 実際の右側の値は right_goal に格納します。
//!
bool ModeSpeakScript::CalculateMessageArea( const std::string& message,Rect& area,int& right_goal )
{
	if ( message.empty() )
	{
		return false;
	}
	const auto line_index = static_cast<int>(message_list.size());
	const auto message_top = MSG_SET_Y + MSG_LINE_GRID_HEIGHT * line_index;
	const auto message_bottom = message_top + MSG_LINE_HEIGHT;

	area.Set( MSG_SET_X,message_top,MSG_SET_X,message_bottom );

	const auto string_lenght = static_cast<int>(std::strlen( message.c_str() ));

	right_goal = MSG_SET_X + ((string_lenght + 2) * (FONT_SIZE / 2));

	return true;
}

//!
//! @fn bool ScriptEngine::GetImageHandle(const std::string& str, int& handle) const
//! @brief 画像ラベル文字列より画像ハンドルを取得
//! @param[in] str 画像ラベル文字列
//! @param[out] handle 画像ハンドル
//! @return 処理の成否
//! @details 画像ハンドルは、DX ライブラリの
//! 画像ロード関数で得られる描画用の値です。
//!
bool ModeSpeakScript::GetImageHandle( const std::string& str,int& handle ) const
{
	for ( auto&& image : image_list )
	{
		if ( image->GetLabel() == str )
		{
			handle = image->GetHandle();

			return true;
		}
	}

	return false;
}

/**
 * @fn bool ScriptEngine::GetseHandle ( const std::string& str, int& handle ) const
 * @brief 音ラベル文字列より画像ハンドルを取得
 * @param[in] str 音ラベル文字列
 * @param[out] handle 音ハンドル
 * @return 処理の成否
 * @details 画像ハンドルは、DX ライブラリの
 * 音ロード関数で得られる描画用の値です。.
 */
bool ModeSpeakScript::GetSeHandle( const std::string& str,int& handle ) const
{
	for ( auto&& se : se_list )
	{
		if ( se->GetLabel() == str )
		{
			handle = se->GetHandle();

			return true;
		}
	}

	return false;
}

/**
 * ScriptEngine::OnCommandPlayanime ( unsigned int line, const std::vector<std::string>& scripts ).
 * brief　スクリプトの "ve" コマンドを処理
 * \param line
 * \param scripts
 * \return 処理の是非
 */
bool ModeSpeakScript::OnCommandPlayanime( unsigned int line,const std::vector<std::string>& scripts )
{
	movie_play = std::make_unique<CommandMoviePlay>( line,scripts );
	if ( !movie_play->Check() )
	{
		return false;
	}
	auto mvhandle = 0;

	if ( !GetImageHandle( movie_play->GetLabel(),mvhandle ) )
	{
		return false;
	}
	movie_play->SetMvHandle( mvhandle );

	SeekMovieToGraph( movie_play->GetMvHandle(),0 );
	PlayMovieToGraph( movie_play->GetMvHandle() );

	state = ScriptState::PLAY_ANIME;

	return true;
};

/**
 * bool ScriptEngine::OnCommandMusicloop( unsigned int line, const std::vector<std::string>& scripts ).
 * brief　スクリプトの "bg" コマンドを処理
 * \param line
 * \param scripts
 * \return 処理の是非
 */
bool ModeSpeakScript::OnCommandMusicloop( unsigned int line,const std::vector<std::string>& scripts )
{
	auto  mgloop = std::make_unique<CommandMusicLoop>( line,scripts );
	if ( !mgloop->Check() )
	{
		return false;
	}
	auto bghandle = 0;
	if ( !GetSeHandle( mgloop->GetLabel(),bghandle ) )
	{
		return false;
	}

	mgloop->SetMgHandle( bghandle );
	PlaySoundMem( mgloop->GetMgHandle(),DX_PLAYTYPE_LOOP );
	return true;
};

/**
 * bool ScriptEngine::OnCommandMusicbag ( unsigned int line, const std::vector<std::string>& scripts ).
 * brief　スクリプトの "fg" コマンドを処理
 * \param line
 * \param scripts
 * \return 処理の是非
 */
bool ModeSpeakScript::OnCommandMusicbag( unsigned int line,const std::vector<std::string>& scripts )
{
	auto  mgbag = std::make_unique<CommandMusicBack>( line,scripts );
	if ( !mgbag->Check() )
	{
		return false;
	}
	auto bghandle = 0;

	if ( !GetSeHandle( mgbag->GetLabel(),bghandle ) )
	{
		return false;
	}

	mgbag->SetMgHandle( bghandle );
	PlaySoundMem( mgbag->GetMgHandle(),DX_PLAYTYPE_BACK );
	return true;
};

/**
 * bool ScriptEngine::OnCommandMusicstop ( unsigned int line, const std::vector<std::string>& scripts ).
 * brief　スクリプトの "gs" コマンドを処理
 * \param line
 * \param scripts
 * \return 処理の是非
 */
bool ModeSpeakScript::OnCommandMusicstop( unsigned int line,const std::vector<std::string>& scripts )
{
	auto  mgstop = std::make_unique<CommandMusicStop>( line,scripts );
	if ( !mgstop->Check() )
	{
		return false;
	}
	auto bghandle = 0;

	if ( !GetSeHandle( mgstop->GetLabel(),bghandle ) )
	{
		return false;
	}

	mgstop->SetMgHandle( bghandle );
	StopSoundMem( mgstop->GetMgHandle() );
	return true;
};

//!
//! @fn void ScriptEngine::OnCommandClick()
//! @brief スクリプトの '@' コマンドを処理
//!
bool ModeSpeakScript::OnCommandClick( unsigned int line,const std::vector<std::string>& scripts )
{
	if ( _game.Getinput().GetTrgXinput( XINPUT_BUTTON_A ) )
	{

		image_list.clear();
		state = ScriptState::PARSING;
	}
	else
	{
		state = ScriptState::CLICK_WAIT;
	}
	return true;
}

//!
//! @fn bool ScriptEngine::OnCommandWait(const std::vector<std::string>& scripts)
//! @brief スクリプトの 'w' コマンドを処理
//! @param[in] scripts スクリプトの内容
//! @return 処理の成否
//!
bool ModeSpeakScript::OnCommandWait( unsigned int line,const std::vector<std::string>& scripts )
{
	auto wait = 0;
	auto result = false;

	if ( string::ToInt( scripts[1],wait ) )
	{
		wait_count = static_cast<unsigned int>(wait);
		state = ScriptState::TIME_WAIT;
		result = true;
	}

	return result;
}

/**
 * @fn bool ScriptEngine::OnCommandscliptend(const std::vector<std::string>& scripts).
 * @brief スクリプトの "e" コマンドを処理
 * \param line
 * \param scripts
 * \return 処理の成否
 */
bool ModeSpeakScript::OnCommandScriptend( unsigned int line,const std::vector<std::string>& scripts )
{
//	_game.isEndsclipt = true;
	for ( auto&& se : se_list )
	{
		StopSoundMem( se->GetHandle() );
	}
	state = ScriptState::SCRIPT_END;
	return true;
}

//!
//! @fn bool ScriptEngine::OnCommandImage(unsigned int line, const std::vector<std::string>& scripts)
//! @brief スクリプトの 'i' コマンドを処理
//! @param[in] line スクリプトの行数
//! @param[in] scripts スクリプトの内容
//! @return 処理の成否
//!
bool ModeSpeakScript::OnCommandImage( unsigned int line,const std::vector<std::string>& scripts )
{
	auto  image = std::make_unique<CommandImageLoad>( line,scripts );
	if ( !image->Check() )
	{
		return false;
	}

	image_list.emplace_back( std::move( image ) );

	return true;
}

/**
 * @fn bool ScriptEngine::OnCommandSe ( unsigned int line, const std::vector<std::string>& scripts )
 * @brief スクリプトの 'im' コマンドを処理
 * @param[in] line スクリプトの行数
 * @param[in] scripts スクリプトの内容
 * \return 処理の成否
 */
bool ModeSpeakScript::OnCommandSe( unsigned int line,const std::vector<std::string>& scripts )
{
	auto  se = std::make_unique<CommandSeLoad>( line,scripts );
	if ( !se->Check() )
	{
		return false;
	}

	se_list.emplace_back( std::move( se ) );

	return true;
}

//!
//! @fn bool ScriptEngine::OnCommandMessage(unsigned int line, const std::vector<std::string>& scripts)
//! @brief スクリプトの 'm' コマンドを処理
//! @param[in] line スクリプトの行数
//! @param[in] scripts スクリプトの内容
//! @return 処理の成否
//!
bool ModeSpeakScript::OnCommandMessage( unsigned int line,const std::vector<std::string>& scripts )
{
	auto message = std::make_unique < CommandMessage >( line,scripts );
	if ( !message->Check() )
	{
		return false;
	}

	Rect rect;
	int right_goal = 0;

	if ( !CalculateMessageArea( message->GetMessageA(),rect,right_goal ) )
	{
		return false;
	}

	message->Initialize( std::move( rect ),right_goal );

	const auto size = static_cast<int>(message_list.size());

	// 最大メッセージライン数を超えたら先頭(インデックス 0 )を削除
	if ( size > MSG_LINE_MAX )
	{
		message_list.erase( message_list.begin() + 0 );
	}

	message_list.emplace_back( std::move( message ) );

	// メッセージコマンドを処理したらメッセージ表示を有効にする
	is_message_output = true;

	return true;
}

/**
 * .
 * @brief スクリプトの "di" コマンドを処理
 * \param line スクリプトの行数
 * \param scripts スクリプトの内容
 * \return 処理の成否
 */
bool ModeSpeakScript::OnCommandDrawin( unsigned int line,const std::vector<std::string>& scripts )
{

	auto drawin = std::make_unique<CommandDrawIn>( line,scripts );
	if ( !drawin->Check() )
	{
		return false;
	}

	auto handle = 0;

	if ( !GetImageHandle( drawin->GetLabel(),handle ) )
	{
		return false;
	}

	drawin->SetHandle( handle );

	// 同じ Index の Draw コマンドを消す(上書き仕様)
	const auto index = drawin->GetIndex();
	const auto check = [index]( const auto& element ) -> bool
	{
		return element->GetIndex() == index;
	};
	const auto remove = std::remove_if( drawin_list.begin(),drawin_list.end(),check );

	drawin_list.erase( remove,drawin_list.end() );
	drawin_list.emplace_back( std::move( drawin ) );

	// 描画リストが複数あるなら Index でソートする
	if ( drawin_list.size() >= 2 )
	{
		const auto sort = []( const auto& lh,const auto& rh ) -> bool
		{
			return lh->GetIndex() < rh->GetIndex();
		};

		std::sort( drawin_list.begin(),drawin_list.end(),sort );
	}

	return true;
};

/**
 * .
 * @brief スクリプトの "do" コマンドを処理
 * \param line スクリプトの行数
 * \param scripts スクリプトの内容
 * \return 処理の成否
 */
bool ModeSpeakScript::OnCommandDrawout( unsigned int line,const std::vector<std::string>& scripts )
{

	drawin_list.clear();
	auto drawout = std::make_unique<CommandDrawOut>( line,scripts );
	if ( !drawout->Check() )
	{
		return false;
	}

	auto handle = 0;

	if ( !GetImageHandle( drawout->GetLabel(),handle ) )
	{
		return false;
	}


	drawout->SetHandle( handle );

	// 同じ Index の Draw コマンドを消す(上書き仕様)
	const auto index = drawout->GetIndex();
	const auto check = [index]( const auto& element ) -> bool
	{
		return element->GetIndex() == index;
	};
	const auto remove = std::remove_if( drawout_list.begin(),drawout_list.end(),check );

	drawout_list.erase( remove,drawout_list.end() );
	drawout_list.emplace_back( std::move( drawout ) );

	// 描画リストが複数あるなら Index でソートする
	if ( drawout_list.size() >= 2 )
	{
		const auto sort = []( const auto& lh,const auto& rh ) -> bool
		{
			return lh->GetIndex() < rh->GetIndex();
		};

		std::sort( drawout_list.begin(),drawout_list.end(),sort );
	}

	return true;
};

/**
 * @fn bool ScriptEngine::OnCommandCrfi(unsigned int line, const std::vector<std::string>& scripts)
 * @brief スクリプトの 'fi' コマンドを処理
 * \param [in] scripts スクリプトの内容
 * \param [in] scripts スクリプトの内容
 * \return 処理の成否
 */
bool ModeSpeakScript::OnCommandCrfi( unsigned int line,const std::vector<std::string>& scripts )
{
	crfo_list.clear();
	auto crfi = std::make_unique<CommandCrFeedIn>( line,scripts );
	if ( !crfi->Check() )
	{
		return false;
	}
	feedcount = static_cast<double>(crfi->GetinCount());
	crfi_list.emplace_back( std::move( crfi ) );
	_Alpha = 255.0;
	state = ScriptState::CRFEEDIN;

	return  true;
}

/**
 * @fn bool ScriptEngine::OnCommandCrfo(unsigned int line, const std::vector<std::string>& scripts)
 * @brief スクリプトの "fo" コマンドを処理
 * \param [in] scripts スクリプトの内容
 * \param [in] scripts スクリプトの内容
 * \return 処理の成否
 */
bool ModeSpeakScript::OnCommandCrfo( unsigned int line,const std::vector<std::string>& scripts )
{
	crfi_list.clear();
	auto crfo = std::make_unique<CommandCrFeedOut>( line,scripts );
	if ( !crfo->Check() )
	{
		return false;
	}
	feedcount = static_cast<double>(crfo->GetoutCount());
	crfo_list.emplace_back( std::move( crfo ) );
	_Alpha = 0.0;
	state = ScriptState::CRFEEDOUT;
	return true;
}

/**
 *¥fn void script_engine::Render.
 *¥brief スクリプトの全ての描画処理
 * 毎フレーム呼び出す必要があります。
 *¥return void
 */
bool ModeSpeakScript::Draw()
{
	RenderImage();//イラスト描画
	RenderFeedin();//フェードイン時描画
	RenderFeedout();
	SetDrawBlendMode( DX_BLENDMODE_ALPHA,Hide_point );
	RenderMessageWindow();
	RenderMessage();
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	RenderAnime();
	return true;
}

/**
 *¥fn void script_engine::RenderImage.
 *¥brief "di""do" コマンドによる画像描画
 *¥return void
 */
void ModeSpeakScript::RenderImage() const
{
	if ( _game.GetScliptFlagManager()->GetisBlackbackground() )//必要に応じてスクリプトの後ろに映っているモノを隠す描画
	{
		if ( state == ScriptState::CRFEEDIN || !(drawout_list.empty()) )
		{
		}
		else
		{
			DrawBox( 0,0,_game.DispSizeW(),_game.DispSizeH(),GetColor( 255,255,255 ),TRUE );
		}
	}
	for ( auto&& drawin : drawin_list )//現れる描画
	{
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,static_cast<int>(drawin->GetDrawAlphain()) );
		DrawGraph( drawin->GetX(),drawin->GetY(),drawin->GetHandle(),TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}

	for ( auto&& drawout : drawout_list )//消えていく描画
	{
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,static_cast<int>(drawout->GetDrawAlphaout()) );
		DrawGraph( drawout->GetX(),drawout->GetY(),drawout->GetHandle(),TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}
}

/**
 *¥fn void script_engine::RenderMessage.
 *¥brief "m" コマンドによる文字列描画
 *¥return void
 */
void ModeSpeakScript::RenderMessage() const
{
	for ( auto&& message : message_list )
	{
		auto LINE_POSITION_RIGHT = LINE_POSITION_LEFT + ((static_cast<int>(message->Whospeak().size())) / 2 * FONT_SIZE);
		DrawBox( LINE_POSITION_LEFT,LINE_POSITION_TOP,LINE_POSITION_RIGHT,LINE_POSITION_BOTTOM,message_string_color,TRUE );
		DrawString( MSG_SPEAKER_SET_X,MSG_SPEAKER_SET_Y,message->Whospeak().c_str(),message_string_color );
		const auto& area = message->GetArea();
		// 表示エリアを制御して 1文字づつ描画する
		SetDrawArea( static_cast<int>(area.leftTop.x),
								 static_cast<int>(area.leftTop.y),
								 static_cast<int>(area.rightBottom.x),
								 static_cast<int>(area.rightBottom.y) );

		DrawString( static_cast<int>(area.leftTop.x),
								static_cast<int>(area.leftTop.y),
								message->GetMessageA().c_str(),
								message_string_color );
	}
	// 表示エリアを全画面に戻す
	SetDrawArea( 0,0,screen_width,screen_height );


	if ( is_click_wait_visible )
	{
		if ( is_hide )
		{
		}
		else
		{

		}
	}
}

/**
 *¥fn void script_engine::RenderMessageWindow.
 *¥brief メッセージウィンドウの描画
 *¥return void
 */
void ModeSpeakScript::RenderMessageWindow() const
{
	if ( (message_list.empty()) )
	{
	}
	else
	{
		//DrawGraph( MSG_WINDOW_LEFT,MSG_WINDOW_TOP,_game._cgTextbox,TRUE );
	}
}

/**
 *¥fn void script_engine::RenderFeedin.
 *¥brief "fi" コマンドによる描画
 *¥return void
 */
void ModeSpeakScript::RenderFeedin()const
{
	for ( auto&& crfi : crfi_list )
	{
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,static_cast<int>(_Alpha) );
		DrawBox( 0,0,_game.DispSizeW(),_game.DispSizeH(),GetColor( crfi->GetRed(),crfi->GetGreen(),crfi->GetBlue() ),TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}
}

/**
 *¥fn void script_engine::RenderFeedout.
 *¥brief "fo" コマンドによる描画
 *¥return void
 */
void ModeSpeakScript::RenderFeedout()const
{
	for ( auto&& crfo : crfo_list )
	{
		auto color = GetColor( crfo->GetRed(),crfo->GetGreen(),crfo->GetBlue() );
		auto a = static_cast<int>(_Alpha);
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,a );
		DrawBox( 0,0,_game.DispSizeW(),_game.DispSizeH(),color,TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}
}

/**
 *¥fn void script_engine::RenderAnime.
 *¥brief "ve" コマンドによる描画
 *¥return void
 */
void ModeSpeakScript::RenderAnime()const
{
	if ( state == ScriptState::PLAY_ANIME )
	{
		DrawGraph( 0,0,movie_play->GetMvHandle(),TRUE );
	}
};