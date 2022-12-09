#pragma once
#include <memory>
#include <vector>
#include "ModeBase.h"

class ApplicationBase;

class ModeServer
{
	using ModeBasePtr = std::shared_ptr<ModeBase>;
	using TypeModes = std::vector<ModeBasePtr>;	// ���[�h���X�g���`
public:
	ModeServer(ApplicationBase& game);
	~ModeServer();

	TypeModes& GetModes()
	{
		return _vModes;
	}

	void	Clear();
	void	Add(ModeBasePtr mode);
	void	Del(ModeBase& mode);

	bool UpdateInit();
	bool Update();  // �X�V
	bool UpdateFinish();
	bool DrawInit();
	bool Draw();	// �`��
	bool DrawFinish();

protected:
	ApplicationBase& _game;
	TypeModes _vModes;
	TypeModes _vPendingModes;
	bool	_updating;

	void	DeleteModes();
	void	AddPendingModes();


};
