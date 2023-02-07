/*****************************************************************//**
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
	const std::string COMMAND_IL = "imageload";
	const std::string COMMAND_ML = "musicload";
	const std::string COMMAND_FI = "feedin";
	const std::string COMMAND_FO = "feedout";
	const std::string COMMAND_DI = "drawin";
	const std::string COMMAND_DO = "drawout";
	const std::string COMMAND_M = "message";
	const std::string COMMAND_A = "@";
	const std::string COMMAND_W = "wait";
	const std::string COMMAND_BM = "backmusic";
	const std::string COMMAND_LM = "loopmusic";
	const std::string COMMAND_SM = "stopmusic";
	const std::string COMMAND_VE = "video";
	const std::string COMMAND_E = "end";

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

	constexpr auto MSG_WINDOW_WIDTH = 1480;
	constexpr auto MSG_WINDOW_HEIGHT = 270;

	constexpr auto MSG_WINDOW_LEFT = 255;
	constexpr auto MSG_WINDOW_RIGHT = MSG_WINDOW_LEFT + MSG_WINDOW_WIDTH;
	constexpr auto MSG_WINDOW_TOP = 755;
	constexpr auto MSG_WINDOW_BOTTOM = MSG_WINDOW_TOP + MSG_WINDOW_HEIGHT;

	constexpr auto LINE_THICKNESS = 5;
	constexpr auto LINE_POSITION_LEFT = MSG_SPEAKER_SET_X;
	constexpr auto LINE_POSITION_TOP = MSG_SPEAKER_SET_Y + FONT_SIZE;
	constexpr auto LINE_POSITION_BOTTOM = LINE_POSITION_TOP + LINE_THICKNESS;

	constexpr auto CLICK_WAIT_X = 1600;
	constexpr auto CLICK_WAIT_Y = 900;

	constexpr auto SCRIPT_SKIP_TIME = 200;
	constexpr auto ANIME_SKIP_OK_TIME = 120;

	int screen_width = 1920;
	int screen_height = 1080;

	int screen_center_x = screen_width / 2;
	int screen_center_y = screen_height / 2;

	unsigned int message_string_color = 0;
	std::string FILE_PASS = "res/script/";
	std::string FILE_NAME = ".json";
	const std::string DELIMITER = ",";

}

ModeSpeakScript::ModeSpeakScript( ApplicationBase& game,int layer,std::string storyname )
	:ModeBase( game,layer )
{
	auto character_story = string::Split( storyname,"/" );
	FILE_PASS += character_story[0];
	FILE_NAME = character_story[1] + FILE_NAME;
	FILE_PASS += "/";
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
bool ModeSpeakScript::InitializeStrings()
{

	auto screen_depth = 0;

	if ( GetScreenState( &screen_width,&screen_height,&screen_depth ) != 0 )
	{
		return false;
	}
	is_Click_on = false;
	message_string_color = GetColor( 0,255,0 );

	return true;
}

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
			break;
	}

	feed_draw();

	if ( is_Skip_ok )
	{
		Script_skip();
		Hide_Message();
	}


	if ( is_update_message )
	{
		UpdateMessage();
	}
	return true;
}

void ModeSpeakScript::UpdateMessage()
{
	is_click_wait_visible = false;

	for ( auto&& message : message_list )
	{
		const auto& area = message->GetArea();
		const auto right_goal = message->GetRightGoal();

		if ( _game.Getinput().XinputEveryOtherKey( XINPUT_BUTTON_A,20 ) )
		{
			message->UpdateAreaRight( right_goal );
			continue;
		}

		if ( area.rightBottom.x < right_goal )
		{
			message->UpdateAreaRight( static_cast <int>(area.rightBottom.x) + (FONT_SIZE / 2) );
			return;   
		}
	}

	is_message_output = false;

	if ( state == ScriptState::CLICK_WAIT )
	{
		is_click_wait_visible = true;
	}
}


void ModeSpeakScript::PreParsing()
{
	funcs_type comand_funcs;
	comand_funcs.insert( std::make_pair( COMMAND_IL,&ModeSpeakScript::OnCommandImage ) );
	comand_funcs.insert( std::make_pair( COMMAND_ML,&ModeSpeakScript::OnCommandSe ) );

	const auto script = scripts_data->GetScript( now_line,DELIMITER );
	const auto& char_command = (script[0]);
	std::string string_comand{char_command};

	if ( string_comand == COMMAND_ML || string_comand == COMMAND_IL )
	{
		(this->*comand_funcs[string_comand])(now_line,script);
	}

	now_line++;

	if ( now_line >= max_line )
	{
		now_line = 0;
		is_Skip_ok = true;
		state = ScriptState::PARSING;
	}
}

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
	comand_funcs.insert( std::make_pair( COMMAND_LM,&ModeSpeakScript::OnCommandMusicloop ) );
	comand_funcs.insert( std::make_pair( COMMAND_BM,&ModeSpeakScript::OnCommandMusicbag ) );
	comand_funcs.insert( std::make_pair( COMMAND_SM,&ModeSpeakScript::OnCommandMusicstop ) );
	comand_funcs.insert( std::make_pair( COMMAND_VE,&ModeSpeakScript::OnCommandPlayanime ) );
	comand_funcs.insert( std::make_pair( COMMAND_E,&ModeSpeakScript::OnCommandScriptend ) );

	while ( !stop_parsing && (now_line >= 0) && (now_line < max_line) )
	{
		const auto script = scripts_data->GetScript( now_line,DELIMITER );
		const auto& command = (script[0]);
		std::string string_comand{command};

		bool isThrough = false;

		isThrough = (string_comand == COMMAND_IL);
		if ( isThrough == false )
		{
			isThrough = string_comand == COMMAND_ML;
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

bool ModeSpeakScript::OnCommandScriptend( unsigned int line,const std::vector<std::string>& scripts )
{
	for ( auto&& se : se_list )
	{
		StopSoundMem( se->GetHandle() );
	}
	state = ScriptState::SCRIPT_END;
	return true;
}

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

	if ( size > MSG_LINE_MAX )
	{
		message_list.erase( message_list.begin() + 0 );
	}

	message_list.emplace_back( std::move( message ) );

	is_message_output = true;

	return true;
}

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

	const auto index = drawin->GetIndex();
	const auto check = [index]( const auto& element ) -> bool
	{
		return element->GetIndex() == index;
	};
	const auto remove = std::remove_if( drawin_list.begin(),drawin_list.end(),check );

	drawin_list.erase( remove,drawin_list.end() );
	drawin_list.emplace_back( std::move( drawin ) );

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

	const auto index = drawout->GetIndex();
	const auto check = [index]( const auto& element ) -> bool
	{
		return element->GetIndex() == index;
	};
	const auto remove = std::remove_if( drawout_list.begin(),drawout_list.end(),check );

	drawout_list.erase( remove,drawout_list.end() );
	drawout_list.emplace_back( std::move( drawout ) );

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

bool ModeSpeakScript::Draw()
{
	RenderImage();
	RenderFeedin();
	RenderFeedout();
	SetDrawBlendMode( DX_BLENDMODE_ALPHA,Hide_point );
	RenderMessageWindow();
	RenderMessage();
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	RenderAnime();
	return true;
}

void ModeSpeakScript::RenderImage() const
{
	if ( _game.GetScliptFlagManager()->GetisBlackbackground() )
	{
		if ( state == ScriptState::CRFEEDIN || !(drawout_list.empty()) )
		{
		}
		else
		{
			DrawBox( 0,0,_game.DispSizeW(),_game.DispSizeH(),GetColor( 255,255,255 ),TRUE );
		}
	}
	for ( auto&& drawin : drawin_list )
	{
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,static_cast<int>(drawin->GetDrawAlphain()) );
		DrawGraph( drawin->GetX(),drawin->GetY(),drawin->GetHandle(),TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}

	for ( auto&& drawout : drawout_list )
	{
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,static_cast<int>(drawout->GetDrawAlphaout()) );
		DrawGraph( drawout->GetX(),drawout->GetY(),drawout->GetHandle(),TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}
}

void ModeSpeakScript::RenderMessage() const
{
	for ( auto&& message : message_list )
	{
		auto LINE_POSITION_RIGHT = LINE_POSITION_LEFT + ((static_cast<int>(message->Whospeak().size())) / 2 * FONT_SIZE);
		DrawBox( LINE_POSITION_LEFT,LINE_POSITION_TOP,LINE_POSITION_RIGHT,LINE_POSITION_BOTTOM,message_string_color,TRUE );
		DrawString( MSG_SPEAKER_SET_X,MSG_SPEAKER_SET_Y,message->Whospeak().c_str(),message_string_color );
		const auto& area = message->GetArea();
		DrawString( static_cast<int>(area.leftTop.x),
								static_cast<int>(area.leftTop.y),
								message->GetMessageA().c_str(),
								message_string_color );
	}

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

void ModeSpeakScript::RenderMessageWindow() const
{
	if ( (message_list.empty()) )
	{
	}
	else
	{
	}
}

void ModeSpeakScript::RenderFeedin()const
{
	for ( auto&& crfi : crfi_list )
	{
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,static_cast<int>(_Alpha) );
		DrawBox( 0,0,_game.DispSizeW(),_game.DispSizeH(),GetColor( crfi->GetRed(),crfi->GetGreen(),crfi->GetBlue() ),TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}
}

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

void ModeSpeakScript::RenderAnime()const
{
	if ( state == ScriptState::PLAY_ANIME )
	{
		DrawGraph( 0,0,movie_play->GetMvHandle(),TRUE );
	}
};