#pragma once
#include "appframe.h"
#include<vector>
#include<memory>
#include<string>

class ApplicationMain;
class CommandCrfi;
class CommandCrfo;

class ModeMainGame:public ModeBase
{
public:
	ModeMainGame( ApplicationMain& game,int layer );
	virtual ~ModeMainGame();

	void Initialize( std::string jsonpath,std::string scriptsname,std::string jsonname );



	virtual bool Draw();	// �`��

	void Destroy();

	void SetCursor(const vector4& pos) { _vCursor = pos; }

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

	bool OnCommandStageLabel( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandJunpLabel( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandChoice( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandStart( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandEnd( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandLoading( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandFeedIn( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandFeedOut( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandTimeWait( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandClick( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandBgm( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandStory( unsigned int line,const std::vector<std::string>& scripts );



	bool OnCommandStage( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandSkySphere( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandPLayer( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandGunShip( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandEnemyAAA( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandAreaAAA( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandObject( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandAreaObj( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandAreaSpawn( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandSupply( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandCommunication( unsigned int line,const std::vector<std::string>& scripts );
	bool OnCommandNoEntry( unsigned int line,const std::vector<std::string>& scripts );




	/** �G�f�B�b�g���[�h�̎��ɓ���֐� */
	void Edit();
	/** ���͂��ꂽ�R�}���h���Q�[���Ŏg���邩�m�F */
	bool CheckInputString( std::string command );
	/** �ǉ��R�}���h�Ɏg����֐� */
	bool OnEditCommandAdd();
	/** �����R�}���h�Ɏg����֐� */
	bool OnEditCommandDelete();
	/** �������R�}���h�Ɏg����֐� */
	bool OnEditCommandClear();
	/** �ۑ��R�}���h�Ɏg����֐� */
	bool OnEditCommandSave();
	/** �ҏW�n�_�ύX�R�}���h�Ɏg����֐� */
	bool OnEditCommandJunp();
	/** ���t���[���Ă΂�� */
	virtual bool Update();
	/** �t���[�����҂��Ɏg����Update */
	void TimeWait();
	/** �{�^�������܂ő҂Ɏg����Update */
	void ClickWait();
	/** �t�F�[�h�C�����Ɏg����Update */
	void CrfiUpdate();
	/** �t�F�[�h�A�E�g���Ɏg����Update */
	void CrfoUpdate();

	//void DrawFeedin( ApplicationBase& game )const;
	//void DrawFeedout( ApplicationBase& game )const;

	/** ScriptsData�ɃA�N�Z�X����|�C���^ */
	std::unique_ptr<ScriptsData> scripts_data;

	//std::vector<std::unique_ptr<CommandCrfi>> crfi_list;
	//std::vector<std::unique_ptr<CommandCrfo>> crfo_list;

	/** �Q�[���̃X�e�[�^�X */
	ScriptState state;
	/** �Q�[���R�}���h�Ɏg���镶������L�[�Ƃ����֐��|�C���^ */
	using FunctionGameCommand = std::map<std::string,bool(ModeMainGame::*)(unsigned int,const std::vector<std::string>& scripts)>;
	/** �G�f�B�b�g�R�}���h�̎��Ɏg���镶������L�[�Ƃ����֐��|�C���^ */
	using FunctionEditCommand = std::map<std::string,bool(ModeMainGame::*)()>;
	/** �X�N���v�g�̍ő�s�� */
	unsigned int max_line;
	/** ���̍s�� */
	unsigned int now_line;
	/** �҂��� */
	unsigned int wait_count;
	/** �t�F�[�h�A�E�g�C������Ƃ��Ɏg�����l */
	double Alpha;
	/** �t�F�[�h�A�E�g�C������Ƃ��Ɏg���t���[���� */
	double feedcount;
	/** �X�e�[�W�� */
	std::string  stage_name;
	bool is_notcant;
	bool is_notcommand;
	bool is_cannotdelete;

	int _cg;
	int _handlefont;
};
