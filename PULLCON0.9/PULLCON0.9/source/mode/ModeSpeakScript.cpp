//!
//! @file script_engine.cpp
//!
//! @brief �X�N���v�g�G���W���̎���
//!
//! @details �X�N���v�g�̉��
//!
/*�R�}���h�ꗗ
///////////// ����1�t���[��1/60�b�Ȃ̂�60�ƂȂ�ƂP�b�ɂȂ�܂�//////////////////
////////////���̉�ʐݒ��1920��1080�Ȃ̂ň�ԍ���̍��W���i0,0�j��ԉE�����i1920,1080�j�ɂȂ�܂�//////////
/// �Ăэ��݂̓X�N���v�g��ԍŏ��ɏ����Ă����������܂������Ȃ��ꍇ������܂�//
/// �p�X����͂���Ƃ�./resourcefile/�������Ă���t�@�C�����������Ă����������܂��Ăэ��߂܂���///
�摜�A����Ăэ���
"i,�摜��,�摜�p�X",
����F"i,�e�L�X�g�{�b�N�X,./resourcefile/text_box.png",
���n�Ăэ���
"im,����,���p�X",
����F"im,���艹,./resourcefile/se/yes_effect.mp3",
�J���[�t�F�[�h�C��
"fi, �t���[����,�Ԃ̐F�i�K,�΂̐F�i�K,�̐F�i�K",
����F"fi,120,255,0,0",��������Ɖ�ʂ�2�b�����Ă��񂾂�Ԃ��Ȃ��čs���܂�
�J���[�t�F�[�h�A�E�g
"fo, �t���[����,�Ԃ̐F�i�K,�΂̐F�i�K,�̐F�i�K",
����F"fo,60,0,0,0",��������Ɖ�ʂ�1�b�����ĉ�ʂ������瓧���ɂȂ��čs���܂�
�摜�t�F�[�h�C��
"di,�`�悷�鏇��,�����W,�����W,�t���[����,�摜��",
����F"di,0,0,0,60,�e�L�X�g�{�b�N�X",��������Ɖ�ʍ��W�i0,0�j���C���[�P�Ԗڂ̏���1�b�����ďo�����܂��t��0�ɂ���Ƃ����Ȃ�o�����܂�
�摜�t�F�[�h�A�E�g
"do,�`�悷�鏇��,x���W,y���W,�t���[����,�摜��",
����F"di,2,60,60,120,�e�L�X�g�{�b�N�X",��������Ɖ�ʍ��W�i60,60�j���C���[3�Ԗڂ̏���2�b�����ď����܂��t��0�ɂ���Ƃ����Ȃ�����܂��B
�܂�di�R�}���h�œo�^�����摜��S�������܂�
�Z���t
"m,�N������ׂ邩,�Z���t",
����F"m,�C�[���X,�Z���t",��������ƃC�[���X������ׂ��������ɂȂ�܂��t�ɖ��O���Ȃ��ꍇ�̕\�L���\�ł�
���͑҂�
"��",
a�{�^�������܂ő҂��܂��B�������ꍇ���艹���Ȃ�܂�
�҂�
"w, �t���[����",
����F"w, 300",���������5�b�~�܂��Ă��玟�ɐi�݂܂�
���[�v�Đ�//bgm�Ɏg�p
"bg,����",
����F"bg,���艹",���艹���������[�v���܂������~�߂�܂ł����ƂȂ�܂�
���Đ�//�L����������ׂ鎞����ʉ��Ɏg�p
"fg,����",
����F"fg,���艹",���艹�����Đ����܂�
�����~�߂�//bgm���~�߂����Ƃ��Ɏg�p
"gs,����",
�����~�߂܂�
���[�r�[�Đ�//
"ve,�摜��",
����F"ve,�I�[�v�j���O",�I�[�v�j���O���Đ����܂��B�I��邩�X�^�[�g�{�^�����������Ƃ����ɐi�݂܂�
�R�}���h�I��//
"e",
�X�N���v�g���I���Ƃ��g�p
*/


#include "ModeSpeakScrip.h"

#include "scripts_data.h"

#include "command_imageload.h"
#include "command_seload.h"
#include "command_crfi.h"
#include "command_crfo.h"
#include "command_drawin.h"
#include "command_drawout.h"
#include "command_musicloop.h"
#include "command_musicbag.h"
#include "command_musicstop.h"
#include "command_movieplay.h"
#include "command_message.h"
#include "scripts_string.h"
#include <algorithm>
#include<utility>
#include<stdio.h>

namespace
{
// �X�N���v�g �R�}���h
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

//�����ݒ�
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

	//���b�Z�[�W�E�B���h�E�ݒ�
	constexpr auto MSG_WINDOW_WIDTH = 1480;
	constexpr auto MSG_WINDOW_HEIGHT = 270;

	constexpr auto MSG_WINDOW_LEFT = 255;
	constexpr auto MSG_WINDOW_RIGHT = MSG_WINDOW_LEFT + MSG_WINDOW_WIDTH;
	constexpr auto MSG_WINDOW_TOP = 755;
	constexpr auto MSG_WINDOW_BOTTOM = MSG_WINDOW_TOP + MSG_WINDOW_HEIGHT;

	//���O�̉��̃��C���\���萔
	constexpr auto LINE_THICKNESS = 5;
	constexpr auto LINE_POSITION_LEFT = MSG_SPEAKER_SET_X;
	constexpr auto LINE_POSITION_TOP = MSG_SPEAKER_SET_Y + FONT_SIZE;
	constexpr auto LINE_POSITION_BOTTOM = LINE_POSITION_TOP + LINE_THICKNESS;

	//�N���b�N�҂��摜�̃|�W�V����
	constexpr auto CLICK_WAIT_X = 1600;
	constexpr auto CLICK_WAIT_Y = 900;

	//�X�L�b�v�ݒ�
	constexpr auto SCRIPT_SKIP_TIME = 200;
	constexpr auto ANIME_SKIP_OK_TIME = 120;

		// ��x�v�Z������Œ�l�ȕ�
	int screen_width = SCREEN_W;
	int screen_height = SCREEN_H;

	int screen_center_x = screen_width / 2;
	int screen_center_y = screen_height / 2;

	unsigned int message_string_color = 0;
}

ScriptEngine::ScriptEngine( Game& game,std::string storyname,ModeBase& base )
	:_game( game )
	,_base( base )
{
	movie_play.reset();
	scripts_data.reset();
	scripts_data = std::make_unique<ScriptsData>();
	scripts_data->LoadJson( storyname );
	max_line = scripts_data->GetScriptNum();
	PreParsing();
	InitializeStrings();
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
}

ScriptEngine::~ScriptEngine()
{
	Destroy();
}

//!
//! @fn bool ScriptEngine::InitializeStrings()
//! @brief �X�N���v�g�G���W���p������`��̏�����
//! @return �����̐���
//!
bool ScriptEngine::InitializeStrings()
{
	SetFontSize( FONT_SIZE );

	auto screen_depth = 0;

	if ( GetScreenState( &screen_width,&screen_height,&screen_depth ) != 0 )
	{
		return false;
	}
	is_Click_on = false;
	message_string_color = _game._CrText;

	return true;
}

//!
//! @fn void ScriptEngine::Destroy()
//! @brief �����I�ȃX�N���v�g�G���W���̏I������
//! @details �����ɌĂяo���K�v�͂���܂���
//! �C���X�^���X���ė��p�������ꍇ�ȂǂɌĂяo���܂��B
//!
void ScriptEngine::Destroy()
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
//! @brief �X�N���v�g�G���W���̍X�V����
//! @details ���t���[���Ăяo���K�v������܂��B
//!
void ScriptEngine::Update()
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
			_game.isEndsclipt = true;
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
}

//!
//! @fn void ScriptEngine::UpdateMessage()
//! @brief ������� 1 �����Â\�������鏈��
//!
void ScriptEngine::UpdateMessage()
{
	is_click_wait_visible = false;

	for ( auto&& message : message_list )
	{
		const auto area = message->GetArea();
		const auto right_goal = message->GetRightGoal();

		// �N���b�N���ꂽ��S���b�Z�[�W��\��
		if ( _game._trg & PAD_INPUT_A || is_Click_on )
		{
			message->UpdateAreaRight( right_goal );
			continue;
		}

		// �E�I�[(�S������)�ɂȂ�܂� 1 �����T�C�Y���Â����čs��
		if ( area.right < right_goal )
		{
			message->UpdateAreaRight( area.right + (FONT_SIZE / 2) );
			return; // 1 ���������������烁�\�b�h�I��
		}
	}

	// return ������ for �����I������Ȃ�S�������\�����Ă���
	is_message_output = false;

	if ( state == ScriptState::CLICK_WAIT )
	{
		is_click_wait_visible = true;
	}
}

/**
 *?fn void script_engine.cpp::PreParsing.
 * @brief �X�N���v�g�̎��O���
 * im' �R�}���h(���x��)�� 'i' �R�}���h(�C���[�W)��
 * �\�ߑS�ď������ă��X�g�����܂��B
 *?return void
 */
void ScriptEngine::PreParsing()
{
	funcs_type comand_funcs;
	comand_funcs.insert( std::make_pair( COMMAND_I,&ScriptEngine::OnCommandImage ) );
	comand_funcs.insert( std::make_pair( COMMAND_IM,&ScriptEngine::OnCommandSe ) );

	const auto script = scripts_data->GetScript( now_line );
	const auto char_command = (script[0]);
	std::string string_comand{char_command};

	if ( string_comand == COMMAND_IM || string_comand == COMMAND_I )
	{
		(this->*comand_funcs[string_comand])(now_line,script);
	}

	now_line++;

	if ( now_line >= max_line )
	{
		_game.isLoadend = true;
		now_line = 0;
		is_Skip_ok = true;
		state = ScriptState::PARSING;
	}
}

//!
//! @fn void ScriptEngine::Parsing()
//! @brief �X�N���v�g�̉��
//! @details �X�N���v�g�� 1 �s�P�ʂŏ������܂��B
//! (�C���^�[�v���^����)
//!
void ScriptEngine::Parsing()
{
	is_hide = false;
	is_finishdraw = false;
	Hide_point = 255;
	message_list.clear();
	movie_play.reset();
	auto stop_parsing = false;
	funcs_type comand_funcs;
	comand_funcs.insert( std::make_pair( COMMAND_FI,&ScriptEngine::OnCommandCrfi ) );
	comand_funcs.insert( std::make_pair( COMMAND_FO,&ScriptEngine::OnCommandCrfo ) );
	comand_funcs.insert( std::make_pair( COMMAND_DI,&ScriptEngine::OnCommandDrawin ) );
	comand_funcs.insert( std::make_pair( COMMAND_DO,&ScriptEngine::OnCommandDrawout ) );
	comand_funcs.insert( std::make_pair( COMMAND_M,&ScriptEngine::OnCommandMessage ) );
	comand_funcs.insert( std::make_pair( COMMAND_A,&ScriptEngine::OnCommandClick ) );
	comand_funcs.insert( std::make_pair( COMMAND_W,&ScriptEngine::OnCommandWait ) );
	comand_funcs.insert( std::make_pair( COMMAND_BG,&ScriptEngine::OnCommandMusicloop ) );
	comand_funcs.insert( std::make_pair( COMMAND_FG,&ScriptEngine::OnCommandMusicbag ) );
	comand_funcs.insert( std::make_pair( COMMAND_GS,&ScriptEngine::OnCommandMusicstop ) );
	comand_funcs.insert( std::make_pair( COMMAND_VE,&ScriptEngine::OnCommandPlayanime ) );
	comand_funcs.insert( std::make_pair( COMMAND_E,&ScriptEngine::OnCommandScliptend ) );

	while ( !stop_parsing && (now_line >= 0) && (now_line < max_line) )
	{
		const auto script = scripts_data->GetScript( now_line );
		const auto command = (script[0]);
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
 * @brief di do�R�}���h�v�Z����
 */
void  ScriptEngine::feed_draw()
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
 *?fn void script_engine.cpp::Speakskip.
 *?brief ��b���X�L�b�v����
 *?return void
 */
void  ScriptEngine::Speak_skip()
{
	if ( _game._key & PAD_INPUT_A )
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
 *?fn void script_engine.cpp::Scriptskip.
 *?brief �X�N���v�g���̂��X�L�b�v����
 *?return void
 */
void ScriptEngine::Script_skip()
{
	if ( _game._key & PAD_INPUT_X )
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
 *?fn void script_engine::Hide_Message.
 *?brief
 *?return void
 */
void ScriptEngine::Hide_Message()
{
	if ( (_game._trg & PAD_INPUT_B) && is_hide )
	{
		is_hide = false;
		Hide_point = 255;
	}
	else if ( (_game._trg & PAD_INPUT_B) && !is_hide )
	{
		is_hide = true;
		Hide_point = 0;
	}
};

/**
 * @fn void ScriptEngine::CrfiUpdate ()
 * @brief �X�N���v�g�� "fi" �R�}���h���̌v�Z����
 */
void ScriptEngine::CrfiUpdate()
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
 * @brief �X�N���v�g�� "fo" �R�}���h���̌v�Z����
 */
void ScriptEngine::CrfoUpdate()
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
//! @brief �N���b�N�҂�����
//!
void ScriptEngine::ClickWait()
{
	if ( is_message_output )
	{
		return;
	}
	if ( is_finishdraw )
	{
		if ( _game._trg & PAD_INPUT_A || is_Click_on )
		{
			auto pop = std::make_unique<EffectPop>( _game,_base );
			_game.GetObjectServer().Add( std::move( pop ) );

			is_finishdraw = false;
			PlaySoundMem( _game._se["yes"],DX_PLAYTYPE_BACK );
			state = ScriptState::PARSING;
		}
	}
}

//!
//! @fn void ScriptEngine::TimeWait()
//! @brief ���ԑ҂�����
//!
void ScriptEngine::TimeWait()
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
 * @brief �A�j���Đ�������
 */
void ScriptEngine::PlayUpdate()
{
	Anime_count++;
	if ( Anime_count > ANIME_SKIP_OK_TIME )
	{
		is_amime_skip = true;
	}
	if ( is_amime_skip && (_game._trg & PAD_INPUT_A || (GetMovieStateToGraph( movie_play->GetMvHandle() ) == 0)) )
	{
		is_amime_skip = false;
		Anime_count = 0;
		PauseMovieToGraph( movie_play->GetMvHandle() );
		state = ScriptState::PARSING;
	}
};

//!
//! @fn bool ScriptEngine::CalculateMessageArea(const std::string& message, Rect& area, int& right_goal)
//! @brief ���b�Z�[�W��������\���G���A��E�I�[���v�Z����
//! @param[in] message ���b�Z�[�W������
//! @param[out] area ���b�Z�[�W�\���G���A
//! @param[out] right_goal ���b�Z�[�W�E�I�[
//! @return �����̐���
//! @details ���b�Z�[�W�̏��Ԃ╶�������\���G���A���v�Z���܂��B
//! �\���G���A�̉E���́A�����l�͍����Ɠ��l�Ƃ��܂��B
//! (���w�I�ɂ̓G���A�͖ʐς������Ȃ�)
//! ����͍������� 1 �����Â\�����Ă����d�l�ׂ̈ł��B
//! ���ۂ̉E���̒l�� right_goal �Ɋi�[���܂��B
//!
bool ScriptEngine::CalculateMessageArea( const std::string& message,Rect& area,int& right_goal )
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
//! @brief �摜���x����������摜�n���h�����擾
//! @param[in] str �摜���x��������
//! @param[out] handle �摜�n���h��
//! @return �����̐���
//! @details �摜�n���h���́ADX ���C�u������
//! �摜���[�h�֐��œ�����`��p�̒l�ł��B
//!
bool ScriptEngine::GetImageHandle( const std::string& str,int& handle ) const
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
 * @brief �����x����������摜�n���h�����擾
 * @param[in] str �����x��������
 * @param[out] handle ���n���h��
 * @return �����̐���
 * @details �摜�n���h���́ADX ���C�u������
 * �����[�h�֐��œ�����`��p�̒l�ł��B.
 */
bool ScriptEngine::GetSeHandle( const std::string& str,int& handle ) const
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
 * brief�@�X�N���v�g�� "ve" �R�}���h������
 * \param line
 * \param scripts
 * \return �����̐���
 */
bool ScriptEngine::OnCommandPlayanime( unsigned int line,const std::vector<std::string>& scripts )
{
	movie_play = std::make_unique<CommandMovieplay>( line,scripts );
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
 * brief�@�X�N���v�g�� "bg" �R�}���h������
 * \param line
 * \param scripts
 * \return �����̐���
 */
bool ScriptEngine::OnCommandMusicloop( unsigned int line,const std::vector<std::string>& scripts )
{
	auto  mgloop = std::make_unique<CommandMusicloop>( line,scripts );
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
 * brief�@�X�N���v�g�� "fg" �R�}���h������
 * \param line
 * \param scripts
 * \return �����̐���
 */
bool ScriptEngine::OnCommandMusicbag( unsigned int line,const std::vector<std::string>& scripts )
{
	auto  mgbag = std::make_unique<CommandMusicbag>( line,scripts );
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
 * brief�@�X�N���v�g�� "gs" �R�}���h������
 * \param line
 * \param scripts
 * \return �����̐���
 */
bool ScriptEngine::OnCommandMusicstop( unsigned int line,const std::vector<std::string>& scripts )
{
	auto  mgstop = std::make_unique<CommandMusicstop>( line,scripts );
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
//! @brief �X�N���v�g�� '@' �R�}���h������
//!
bool ScriptEngine::OnCommandClick( unsigned int line,const std::vector<std::string>& scripts )
{
	if ( _game._trg & PAD_INPUT_A )
	{
		PlaySoundMem( _game._se["yes"],DX_PLAYTYPE_BACK );
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
//! @brief �X�N���v�g�� 'w' �R�}���h������
//! @param[in] scripts �X�N���v�g�̓��e
//! @return �����̐���
//!
bool ScriptEngine::OnCommandWait( unsigned int line,const std::vector<std::string>& scripts )
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
 * @brief �X�N���v�g�� "e" �R�}���h������
 * \param line
 * \param scripts
 * \return �����̐���
 */
bool ScriptEngine::OnCommandScliptend( unsigned int line,const std::vector<std::string>& scripts )
{
	_game.isEndsclipt = true;
	for ( auto&& se : se_list )
	{
		StopSoundMem( se->GetHandle() );
	}
	state = ScriptState::SCRIPT_END;
	return true;
}

//!
//! @fn bool ScriptEngine::OnCommandImage(unsigned int line, const std::vector<std::string>& scripts)
//! @brief �X�N���v�g�� 'i' �R�}���h������
//! @param[in] line �X�N���v�g�̍s��
//! @param[in] scripts �X�N���v�g�̓��e
//! @return �����̐���
//!
bool ScriptEngine::OnCommandImage( unsigned int line,const std::vector<std::string>& scripts )
{
	auto  image = std::make_unique<CommandImageload>( line,scripts );
	if ( !image->Check() )
	{
		return false;
	}

	image_list.emplace_back( std::move( image ) );

	return true;
}

/**
 * @fn bool ScriptEngine::OnCommandSe ( unsigned int line, const std::vector<std::string>& scripts )
 * @brief �X�N���v�g�� 'im' �R�}���h������
 * @param[in] line �X�N���v�g�̍s��
 * @param[in] scripts �X�N���v�g�̓��e
 * \return �����̐���
 */
bool ScriptEngine::OnCommandSe( unsigned int line,const std::vector<std::string>& scripts )
{
	auto  se = std::make_unique<CommandSeload>( line,scripts );
	if ( !se->Check() )
	{
		return false;
	}

	se_list.emplace_back( std::move( se ) );

	return true;
}

//!
//! @fn bool ScriptEngine::OnCommandMessage(unsigned int line, const std::vector<std::string>& scripts)
//! @brief �X�N���v�g�� 'm' �R�}���h������
//! @param[in] line �X�N���v�g�̍s��
//! @param[in] scripts �X�N���v�g�̓��e
//! @return �����̐���
//!
bool ScriptEngine::OnCommandMessage( unsigned int line,const std::vector<std::string>& scripts )
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

	// �ő僁�b�Z�[�W���C�����𒴂�����擪(�C���f�b�N�X 0 )���폜
	if ( size > MSG_LINE_MAX )
	{
		message_list.erase( message_list.begin() + 0 );
	}

	message_list.emplace_back( std::move( message ) );

	// ���b�Z�[�W�R�}���h�����������烁�b�Z�[�W�\����L���ɂ���
	is_message_output = true;

	return true;
}

/**
 * .
 * @brief �X�N���v�g�� "di" �R�}���h������
 * \param line �X�N���v�g�̍s��
 * \param scripts �X�N���v�g�̓��e
 * \return �����̐���
 */
bool ScriptEngine::OnCommandDrawin( unsigned int line,const std::vector<std::string>& scripts )
{

	auto drawin = std::make_unique<CommandDrawin>( line,scripts );
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

	// ���� Index �� Draw �R�}���h������(�㏑���d�l)
	const auto index = drawin->GetIndex();
	const auto check = [index]( const auto& element ) -> bool
	{
		return element->GetIndex() == index;
	};
	const auto remove = std::remove_if( drawin_list.begin(),drawin_list.end(),check );

	drawin_list.erase( remove,drawin_list.end() );
	drawin_list.emplace_back( std::move( drawin ) );

	// �`�惊�X�g����������Ȃ� Index �Ń\�[�g����
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
 * @brief �X�N���v�g�� "do" �R�}���h������
 * \param line �X�N���v�g�̍s��
 * \param scripts �X�N���v�g�̓��e
 * \return �����̐���
 */
bool ScriptEngine::OnCommandDrawout( unsigned int line,const std::vector<std::string>& scripts )
{

	drawin_list.clear();
	auto drawout = std::make_unique<CommandDrawout>( line,scripts );
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

	// ���� Index �� Draw �R�}���h������(�㏑���d�l)
	const auto index = drawout->GetIndex();
	const auto check = [index]( const auto& element ) -> bool
	{
		return element->GetIndex() == index;
	};
	const auto remove = std::remove_if( drawout_list.begin(),drawout_list.end(),check );

	drawout_list.erase( remove,drawout_list.end() );
	drawout_list.emplace_back( std::move( drawout ) );

	// �`�惊�X�g����������Ȃ� Index �Ń\�[�g����
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
 * @brief �X�N���v�g�� 'fi' �R�}���h������
 * \param [in] scripts �X�N���v�g�̓��e
 * \param [in] scripts �X�N���v�g�̓��e
 * \return �����̐���
 */
bool ScriptEngine::OnCommandCrfi( unsigned int line,const std::vector<std::string>& scripts )
{
	crfo_list.clear();
	auto crfi = std::make_unique<CommandCrfi>( line,scripts );
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
 * @brief �X�N���v�g�� "fo" �R�}���h������
 * \param [in] scripts �X�N���v�g�̓��e
 * \param [in] scripts �X�N���v�g�̓��e
 * \return �����̐���
 */
bool ScriptEngine::OnCommandCrfo( unsigned int line,const std::vector<std::string>& scripts )
{
	crfi_list.clear();
	auto crfo = std::make_unique<CommandCrfo>( line,scripts );
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
 *?fn void script_engine::Render.
 *?brief �X�N���v�g�̑S�Ă̕`�揈��
 * ���t���[���Ăяo���K�v������܂��B
 *?return void
 */
void ScriptEngine::Render() const
{
	RenderImage();//�C���X�g�`��
	RenderFeedin();//�t�F�[�h�C�����`��
	RenderFeedout();
	SetDrawBlendMode( DX_BLENDMODE_ALPHA,Hide_point );
	RenderMessageWindow();
	RenderMessage();
	SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	RenderAnime();
}

/**
 *?fn void script_engine::RenderImage.
 *?brief "di""do" �R�}���h�ɂ��摜�`��
 *?return void
 */
void ScriptEngine::RenderImage() const
{
	if ( _game.isBlackbackground )//�K�v�ɉ����ăX�N���v�g�̌��ɉf���Ă��郂�m���B���`��
	{
		if ( state == ScriptState::CRFEEDIN || !(drawout_list.empty()) )
		{
		}
		else
		{
			DrawBox( BASICS_X,BASICS_Y,SCREEN_W,SCREEN_H,_game._CrBrack,TRUE );
		}
	}
	for ( auto&& drawin : drawin_list )//�����`��
	{
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,static_cast<int>(drawin->GetDrawAlphain()) );
		DrawGraph( drawin->GetX(),drawin->GetY(),drawin->GetHandle(),TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}

	for ( auto&& drawout : drawout_list )//�����Ă����`��
	{
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,static_cast<int>(drawout->GetDrawAlphaout()) );
		DrawGraph( drawout->GetX(),drawout->GetY(),drawout->GetHandle(),TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}
}

/**
 *?fn void script_engine::RenderMessage.
 *?brief "m" �R�}���h�ɂ�镶����`��
 *?return void
 */
void ScriptEngine::RenderMessage() const
{

	for ( auto&& message : message_list )
	{
		auto LINE_POSITION_RIGHT = LINE_POSITION_LEFT + ((static_cast<int>(message->Whospeak().size())) / 2 * FONT_SIZE);
		DrawBox( LINE_POSITION_LEFT,LINE_POSITION_TOP,LINE_POSITION_RIGHT,LINE_POSITION_BOTTOM,message_string_color,TRUE );
		DrawString( MSG_SPEAKER_SET_X,MSG_SPEAKER_SET_Y,message->Whospeak().c_str(),message_string_color );
		const auto area = message->GetArea();
		// �\���G���A�𐧌䂵�� 1�����Â`�悷��
		SetDrawArea( area.left,area.top,area.right,area.bottom );
		DrawString( area.left,area.top,message->GetMessageA().c_str(),message_string_color );
	}
	// �\���G���A��S��ʂɖ߂�
	SetDrawArea( 0,0,screen_width,screen_height );

	//
	if ( is_click_wait_visible )
	{
		if ( is_hide )
		{
		}
		else
		{
			SetDrawBlendMode( DX_BLENDMODE_ALPHA,_base._Modealpha );
			DrawGraph( CLICK_WAIT_X,CLICK_WAIT_Y,_game._cgicon,TRUE );
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
		}
	}
}

/**
 *?fn void script_engine::RenderMessageWindow.
 *?brief ���b�Z�[�W�E�B���h�E�̕`��
 *?return void
 */
void ScriptEngine::RenderMessageWindow() const
{
	if ( (message_list.empty()) )
	{
	}
	else
	{
		DrawGraph( MSG_WINDOW_LEFT,MSG_WINDOW_TOP,_game._cgTextbox,TRUE );
	}
}

/**
 *?fn void script_engine::RenderFeedin.
 *?brief "fi" �R�}���h�ɂ��`��
 *?return void
 */
void ScriptEngine::RenderFeedin()const
{
	for ( auto&& crfi : crfi_list )
	{
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,static_cast<int>(_Alpha) );
		DrawBox( BASICS_X,BASICS_Y,SCREEN_W,SCREEN_H,GetColor( crfi->GetRed(),crfi->GetGreen(),crfi->GetBlue() ),TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}
}

/**
 *?fn void script_engine::RenderFeedout.
 *?brief "fo" �R�}���h�ɂ��`��
 *?return void
 */
void ScriptEngine::RenderFeedout()const
{
	for ( auto&& crfo : crfo_list )
	{
		auto color = GetColor( crfo->GetRed(),crfo->GetGreen(),crfo->GetBlue() );
		auto a = static_cast<int>(_Alpha);
		SetDrawBlendMode( DX_BLENDMODE_ALPHA,a );
		DrawBox( BASICS_X,BASICS_Y,SCREEN_W,SCREEN_H,color,TRUE );
		SetDrawBlendMode( DX_BLENDMODE_NOBLEND,0 );
	}
}

/**
 *?fn void script_engine::RenderAnime.
 *?brief "ve" �R�}���h�ɂ��`��
 *?return void
 */
void ScriptEngine::RenderAnime()const
{
	if ( state == ScriptState::PLAY_ANIME )
	{
		DrawGraph( 0,0,movie_play->GetMvHandle(),TRUE );
	}
};