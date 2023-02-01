/*****************************************************************//**
 * @file   ModeMainGame.h
 * @brief  �Q�[���X�N���v�g��`
 *
 * @author ���������Y
 * @date   January 2023
 *********************************************************************/
#pragma once
#include "appframe.h"
#include <vector>
#include <memory>
#include <string>
#include <array>

class ApplicationMain;
class CommandLabel;
class CommandChoice;
class ModeMainGame:public ModeBase
{
public:
	/** �R���X�g���N�^ */
	ModeMainGame( ApplicationMain& game,int layer );
	/** �f�X�g���N�^ */
	virtual ~ModeMainGame();
	/** ������ �R���X�g���N�^����� */
	void Initialize( std::string jsonpath,std::string scriptsname,std::string jsonname );
	/** �v�Z ���t���[���Ă΂�� */
	virtual bool Update();
	/** �`�� ���t���[���Ă΂�� */
	virtual bool Draw();
	/** �㏈�� �f�X�g���N�^���Ă� */
	void Destroy();

	void SetCursor( const vector4& pos )
	{
		_vCursor = pos;
	}

	vector4 _vCursor;
	bool _transparence;
	bool _clear;

	// �J���p
	bool	_dbgCollisionDraw;		// �R���W�����\��/��\��
private:
	enum class ScriptState
	{
		EDIT,//�G�f�B�b�g���[�h
		PREPARSING,//�v���p�[�X
		PARSING,
		GAME,
		STORY,
		RESULT,
		CRFEEDIN,
		CRFEEDOUT,
		TIME_WAIT,
		CLICK_WAIT,
		LOADING,
		END,
	};


	void PreParsing();
	void Parsing();

	bool OnCommandStageLabel( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandJumpLabel( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandTurning( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandStart( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandEnd( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandLoading( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandCrFeedIn( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandCrFeedOut( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandTimeWait( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandBgm( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandStory( unsigned int line,std::vector<std::string>& scripts );



	bool OnCommandStage( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandSkySphere( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandPLayer( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandGunShip( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandEnemyAAA( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandAreaAAA( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandObject( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandAreaObj( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandAreaSpawn( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandSupply( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandCommunication( unsigned int line,std::vector<std::string>& scripts );
	bool OnCommandNoEntry( unsigned int line,std::vector<std::string>& scripts );




	/** �G�f�B�b�g���[�h�̎��ɓ���֐� */
	void Edit();
	/** ���͂��ꂽ�R�}���h���Q�[���Ŏg���邩�m�F */
	bool CheckInputString( std::string& command,std::vector < std::string >& _sclipt );
	/** �ėp���͊֐� */
	bool CommandInputString( int posix,int posiy,std::string inputname,std::vector<std::string>& _script );
	/** �ǉ��R�}���h�Ɏg����֐� */
	bool OnEditCommandAdd( const std::string& command );
	/** �����R�}���h�Ɏg����֐� */
	bool OnEditCommandDelete( const std::string& command );
	/** �������R�}���h�Ɏg����֐� */
	bool OnEditCommandClear( const std::string& command );
	/** �ۑ��R�}���h�Ɏg����֐� */
	bool OnEditCommandSave( const std::string& command );
	/** �ҏW�n�_�ύX�R�}���h�Ɏg����֐� */
	bool OnEditCommandJunp( const std::string& command );



	/** �t���[�����҂��Ɏg����Update */
	void TimeWait();
	/** ������ɑΉ������s�����擾 */
	bool GetLineNumber( const std::string& str,unsigned int& line ) const;
	/** �t�F�[�h�C�����Ɏg����Update */
	void CrfiUpdate();
	/** �t�F�[�h�A�E�g���Ɏg����Update */
	void CrfoUpdate();
	/** �t�F�[�h�C���`�� */
	void DrawFeedIn()const;
	/** �t�F�[�h�A�E�g�`�� */
	void DrawFeedOut()const;

	/** ScriptsData�ɃA�N�Z�X����|�C���^ */
	std::unique_ptr<ScriptsData> scripts_data;
	/** �X�e�[�W�����i�[����vector */
	std::vector<std::unique_ptr<CommandLabel>> label_list;
	std::vector < std::unique_ptr < CommandCrFeedIn>> crfi_list;
	std::vector < std::unique_ptr < CommandCrFeedOut>> crfo_list;


	/** �Q�[���̃X�e�[�^�X */
	ScriptState state;
	/** �Q�[���R�}���h�Ɏg���镶������L�[�Ƃ����֐��|�C���^ */
	using FunctionGameCommand = std::map<std::string,bool(ModeMainGame::*)(unsigned int,std::vector<std::string>&)>;
	/** �G�f�B�b�g�R�}���h�̎��Ɏg���镶������L�[�Ƃ����֐��|�C���^ */
	using FunctionEditCommand = std::map<std::string,bool(ModeMainGame::*)(const std::string&)>;
	/** �X�N���v�g�̍ő�s�� */
	unsigned int max_line;
	/** ���̍s�� */
	unsigned int now_line;
	/** �҂��� */
	unsigned int wait_count;
	/** �t�F�[�h�A�E�g�C������Ƃ��Ɏg�����l */
	float alpha;
	/** �t�F�[�h�A�E�g�C������Ƃ��Ɏg���t���[���� */
	float feedcount;
	/** �X�e�[�W�� */
	std::string  stage_name;
	/** �Q�[���X�^�[�g���� */
	int start_time;

	bool is_notcant;
	bool is_notcommand;
	bool is_cannotdelete;

	int _cg;
	int _handlefont;
};
