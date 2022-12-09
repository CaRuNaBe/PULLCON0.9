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
	// _vPendingObjects -> _vObjects に追加
	_vObjects.insert(_vObjects.end(),make_move_iterator(_vPendingObjects.begin()),make_move_iterator(_vPendingObjects.end()));
	// _vPendingObjects をクリア
	_vPendingObjects.clear();
}

void	ObjectServer::Del(ObjectBase& object)
{
	object.Dead();
}

void	ObjectServer::DeleteObjects()
{
	// コンテナをイテレータで回す( eraseがイテレータを要求しているため )
	for(auto ite = _vObjects.begin(); ite != _vObjects.end(); )
	{
		if((*ite)->IsDead())
		{
			ite = _vObjects.erase(ite);		// これでobjectそのものも削除される
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
	DeleteObjects();	// 削除予約されたオブジェクトを削除する
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
