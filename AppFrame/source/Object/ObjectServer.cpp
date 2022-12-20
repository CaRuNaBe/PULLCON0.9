#include "DxLib.h"
#include "ObjectServer.h"
#include"ObjectBase.h"
template<class T>ObjectServer<T>::ObjectServer()
	:_updating( false )
{}

template<class T>ObjectServer<T>::~ObjectServer()
{
	Clear();
}

template<class T>void ObjectServer<T>::Clear()
{
	_vObjects.clear();
}

template<class T>void	ObjectServer<T>::Add( ObjectBasePtr object )
{
	if ( _updating )
	{
		_vPendingObjects.push_back( object );
	}
	else
	{
		_vObjects.push_back( object );
	}
}

template<class T>void	ObjectServer<T>::AddPendingObjects()
{
	// _vPendingObjects -> _vObjects �ɒǉ�
	_vObjects.insert( _vObjects.end(),make_move_iterator( _vPendingObjects.begin() ),make_move_iterator( _vPendingObjects.end() ) );
	// _vPendingObjects ���N���A
	_vPendingObjects.clear();
}

template<class T>void	ObjectServer<T>::Del( ObjectBase& object )
{
	object.Dead();
}

template<class T>void	ObjectServer<T>::DeleteObjects()
{
	// �R���e�i���C�e���[�^�ŉ�( erase���C�e���[�^��v�����Ă��邽�� )
	for ( auto ite = _vObjects.begin(); ite != _vObjects.end(); )
	{
		if ( (*ite)->IsDead() )
		{
			ite = _vObjects.erase( ite );		// �����object���̂��̂��폜�����
		}
		else
		{
			++ite;
		}
	}
}

template<class T>bool	ObjectServer<T>::Update( ApplicationBase& game,ModeBase& mode )
{
	_updating = true;
	for ( auto&& object : _vObjects )
	{
		if ( object->GetUpdateSkip() )
		{
			continue;
		}
		object->Update( game,mode );
	}
	_updating = false;
	AddPendingObjects();
	DeleteObjects();	// �폜�\�񂳂ꂽ�I�u�W�F�N�g���폜����
	return true;
}

template<class T>bool	ObjectServer<T>::Draw( ApplicationBase& game,ModeBase& mode )
{
	for ( auto&& object : _vObjects )
	{
		if ( object->GetDrawSkip() )
		{
			continue;
		}
		object->Draw( game,mode );
	}
	return true;
}
