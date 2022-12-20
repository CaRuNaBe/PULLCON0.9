#pragma once
#include <memory>
#include <vector>
class ApplicationBase;
class ModeBase;
class ObjectBase;
template<class T> class ObjectServer
{
public:
	using ObjectPtr = std::shared_ptr<T>;
	using ObjectBasePtr= std::shared_ptr<ObjectBase>;
	using TypeObjects = std::vector <ObjectPtr >;	// オブジェクトリストを定義
	ObjectServer();
	~ObjectServer();

	TypeObjects& GetObjects()
	{
		return _vObjects;
	}

	void	Clear();
	void	Add( ObjectBasePtr object );
	void	Del( ObjectBase& object );

	bool	Update( ApplicationBase& game,ModeBase& mode );//更新
	bool	Draw( ApplicationBase& game,ModeBase& mode );//描画



protected:
	TypeObjects _vObjects;
	TypeObjects _vPendingObjects;
	bool	_updating;

	void	DeleteObjects();
	void	AddPendingObjects();

};
