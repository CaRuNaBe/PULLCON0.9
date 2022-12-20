#pragma once
#include <memory>
#include <vector>
#include"ObjectBase.h"
class ApplicationBase;
class ModeBase;

template<class T> class ObjectServer
{
public:
	using ObjectPtr = std::shared_ptr<T >;
	using TypeObjects = std::vector <ObjectPtr >;	// �I�u�W�F�N�g���X�g���`
	ObjectServer();
	~ObjectServer();

	TypeObjects& GetObjects()
	{
		return _vObjects;
	}

	void	Clear();
	void	Add( ObjectPtr object );
	void	Del( T& object );

	bool	Update( ApplicationBase& game,ModeBase& mode );//�X�V
	bool	Draw( ApplicationBase& game,ModeBase& mode );



protected:
	TypeObjects _vObjects;
	TypeObjects _vPendingObjects;
	bool	_updating;

	void	DeleteObjects();
	void	AddPendingObjects();

};
