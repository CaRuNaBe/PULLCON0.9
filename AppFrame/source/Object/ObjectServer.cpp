#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectServer.h"

ObjectServer::ObjectServer()
	:_updating(false)
{}

ObjectServer::~ObjectServer()
{
	Clear();
}

void ObjectServer::Clear()
{
	_vObjects.clear();
}

void	ObjectServer::Add(ObjectPtr object)
{
	if(_updating)
	{
		_vPendingObjects.push_back(object);
	}
	else
	{
		_vObjects.push_back(object);
	}
}

void	ObjectServer::AddPendingObjects()
{
	// _vPendingObjects -> _vObjects �ɒǉ�
	_vObjects.insert(_vObjects.end(),make_move_iterator(_vPendingObjects.begin()),make_move_iterator(_vPendingObjects.end()));
	// _vPendingObjects ���N���A
	_vPendingObjects.clear();
}

void	ObjectServer::Del(ObjectBase& object)
{
	object.Dead();
}

void	ObjectServer::DeleteObjects()
{
	// �R���e�i���C�e���[�^�ŉ�( erase���C�e���[�^��v�����Ă��邽�� )
	for(auto ite = _vObjects.begin(); ite != _vObjects.end(); )
	{
		if((*ite)->IsDead())
		{
			ite = _vObjects.erase(ite);		// �����object���̂��̂��폜�����
		}
		else
		{
			++ite;
		}
	}
}

bool	ObjectServer::Update(ApplicationBase& game)
{
	_updating = true;
	for(auto&& object : _vObjects)
	{
		if(object->GetUpdateSkip())
		{
			continue;
		}
		object->Update(game);
	}
	_updating = false;
	AddPendingObjects();
	DeleteObjects();	// �폜�\�񂳂ꂽ�I�u�W�F�N�g���폜����
	return true;
}

bool	ObjectServer::Draw(ApplicationBase& game)
{
	for(auto&& object : _vObjects)
	{
		if(object->GetDrawSkip())
		{
			continue;
		}
		object->Draw(game);
	}
	return true;
}
