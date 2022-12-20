#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectServer.h"

template<typename T>
ObjectServer<T>::ObjectServer()
	:_updating( false )
{}
template<typename T>
ObjectServer<T>::~ObjectServer()
{
	Clear();
}
template<typename T>
void ObjectServer<T>::Clear()
{
	_vObjects.clear();
}
template<typename T>
void	ObjectServer<T>::Add( ObjectPtr object )
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
template<typename T>
void	ObjectServer<T>::AddPendingObjects()
{
	// _vPendingObjects -> _vObjects に追加
	_vObjects.insert( _vObjects.end(),make_move_iterator( _vPendingObjects.begin() ),make_move_iterator( _vPendingObjects.end() ) );
	// _vPendingObjects をクリア
	_vPendingObjects.clear();
}
template<typename T>
void	ObjectServer<T>::Del( T& object )
{
	object.Dead();
}
template<typename T>
void	ObjectServer<T>::DeleteObjects()
{
	// コンテナをイテレータで回す( eraseがイテレータを要求しているため )
	for ( auto ite = _vObjects.begin(); ite != _vObjects.end(); )
	{
		if ( (*ite)->IsDead() )
		{
			ite = _vObjects.erase( ite );		// これでobjectそのものも削除される
		}
		else
		{
			++ite;
		}
	}
}
template<typename T>
bool	ObjectServer<T>::Update( ApplicationBase& game,ModeBase& mode )
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
	DeleteObjects();	// 削除予約されたオブジェクトを削除する
	return true;
}
template<typename T>
bool	ObjectServer<T>::Draw( ApplicationBase& game,ModeBase& mode )
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
