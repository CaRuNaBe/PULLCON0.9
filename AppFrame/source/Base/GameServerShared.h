/*****************************************************************//**
 * \file   GameServer.h
 * \brief  ゲームに登場するものすべてを管理するクラス
 *
 * \author 阿部健太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include <memory>
#include <vector>
#include <algorithm>
template<class T> class GameServerShared
{
	using GameBasePtr = std::shared_ptr<T>;
	using TypeModes = std::vector<GameBasePtr>;
public:
	/** コンストラクタ */
	GameServerShared():_updating( false )
	{}
	/** デストラクタ */
	~GameServerShared()
	{
		Clear();
	}
	/** _vObjects取得 */
	TypeModes& GetObjects()
	{
		return _vObjects;
	}
	/** _vObjects初期化 */
	void Clear()
	{
		_vObjects.clear();
	}
	/** _updatingがtrueの時は追加予約する */
	void Add( GameBasePtr object )
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
	/** 削除予約する */
	void	Del( T& object )
	{
		object.Dead();
	}
	/** 更新処理 毎フレーム呼ばれる */
	bool	Update()
	{
		_updating = true;//処理開始
		for ( auto&& object : _vObjects )
		{
			if ( object->GetUpdateSkip() )
			{
				continue;//スキップする
			}
			object->Update();
		}

		// レイヤーによるソート
		std::sort( _vObjects.begin(),_vObjects.end(),[] ( const GameBasePtr& ch1,const GameBasePtr& ch2 )
		{
			return ch1->GetLayer() < ch2->GetLayer();
		} );

		_updating = false;//処理終了
		AddPendingObjects();//_vObjectsに追加し次のフレームから動かす
		DeleteObjects(); // 削除予約されたオブジェクトを削除する
		return true;
	}
	/** 描画処理 毎フレーム呼ばれる */
	bool	 Draw()
	{
		for ( auto&& object : _vObjects )
		{
			if ( object->GetDrawSkip() )
			{
				continue;//描画スキップ
			}
			object->Draw();
		}
#if _DEBUG
		for ( auto&& object : _vObjects )
		{
			object->DebugDraw();
		}
#endif
		return true;
	}
protected:
	/** 動かすものを入れるコンテナ */
	TypeModes _vObjects;
	/** 後で追加するためのコンテナ */
	TypeModes _vPendingObjects;
	/** _vObjectsを回しているときはtrueにする */
	bool _updating;
	/** Del関数でオブジェクトが死んでいた場合_vObjectsからerase */
	void DeleteObjects()
	{
		// コンテナをイテレータで回す( eraseがイテレータを要求しているため )
		for ( auto ite = _vObjects.begin(); ite != _vObjects.end(); )
		{
			if ( (*ite)->IsDead() )
			{
				ite = _vObjects.erase( ite ); // これでobjectそのものも削除される
			}
			else
			{
				++ite;//次に進める
			}
		}
	}
	/** _vPendingObjects の中にあるものを _vObjects に追加 */
	void AddPendingObjects()
	{
		// _vPendingObjects -> _vObjects に追加
		_vObjects.insert( _vObjects.end(),make_move_iterator( _vPendingObjects.begin() ),make_move_iterator( _vPendingObjects.end() ) );
		// _vPendingObjects をクリア
		_vPendingObjects.clear();
	}
};
