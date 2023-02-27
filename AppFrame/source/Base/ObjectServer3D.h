/*****************************************************************//**
 * \file   ObjectServer.h
 * \brief  ゲームに登場するものすべてを管理するクラス
 *
 * \author 阿部健太郎
 * \date   December 2022
 *********************************************************************/
#pragma once
#include <memory>
#include <vector>
#include "GameBase.h"
template<class T>class ObjectServer3D
{
public:
	using ObjectPtr = std::shared_ptr<T>;//オブジェクトクラスポインタObjectBaseを継承したクラスのみ対応
	using TypeObjects = std::vector <ObjectPtr >;// オブジェクトリストを定義
	/** コンストラクタ */
	ObjectServer3D():_updating( false )
	{}
	/** デストラクタ */
	~ObjectServer3D()
	{
		Clear();
	}
	/** _v3DObjects取得 */
	TypeObjects& Get3DObjects()
	{
		return _v3DObjects;
	}
	/** _vBillboardObjects取得 */
	TypeObjects& GetBillboardObjects()
	{
		return _vBillboardObjects;
	}
	/** 全クリア */
	void Clear()
	{
		Clear3DObjects();
		ClearBillboardObjects();
	}
	/** _v3DObjects初期化 */
	void Clear3DObjects()
	{
		_v3DObjects.clear();
	}
	/** _vBillboardObjects初期化 */
	void ClearBillboardObjects()
	{
		_vBillboardObjects.clear();
	}
	/** _updatingがtrueの時は追加予約する */
	void Add3Dobject( ObjectPtr object )
	{
		if ( _updating )
		{
			_vPending3DObjects.push_back( object );
		}
		else
		{
			_v3DObjects.push_back( object );
		}
	}
	/** _updatingがtrueの時は追加予約する */
	void AddBillboardObject( ObjectPtr object )
	{
		if ( _updating )
		{
			_vPendingBillboardObjects.push_back( object );
		}
		else
		{
			_vBillboardObjects.push_back( object );
		}
	}
	/** 削除予約する */
	void Del( T& object )
	{
		object.Dead();
	}
	/** 更新処理 毎フレーム呼ばれる */
	bool Update()
	{
		_updating = true;//処理開始
		for ( auto&& object : _v3DObjects )
		{
			if ( object->GetUpdateSkip() )
			{
				continue;//スキップする
			}
			object->Update();
		}
		for ( auto&& object : _vBillboardObjects )
		{
			if ( object->GetUpdateSkip() )
			{
				continue;//スキップする
			}
			object->Update();
		}
		_updating = false;//処理終了
		AddPendingObjects();//_v3DObjectsに追加し次のフレームから動かす
		DeleteObjects();// 削除予約されたオブジェクトを削除する
		return true;
	}
	/** 描画処理 毎フレーム呼ばれる */
	bool Draw()
	{
		for ( auto itr = std::rbegin( _v3DObjects ); itr != std::rend( _v3DObjects ); ++itr )
		{
			if ( (*itr)->GetDrawSkip() )
			{
				continue;//描画スキップ
			}
			(*itr)->Draw();
		}
		for ( auto itr = std::rbegin( _vBillboardObjects ); itr != std::rend( _vBillboardObjects ); ++itr )
		{
			if ( (*itr)->GetDrawSkip() )
			{
				continue;//描画スキップ
			}
			(*itr)->Draw();
		}
		return true;
	}
protected:
	/** 3Dオブジェクトを入れるコンテナ */
	TypeObjects _v3DObjects;
	/** 3Dオブジェクトを後で追加するためのコンテナ */
	TypeObjects _vPending3DObjects;
	/** ビルボードで作られたものを入れるコンテナ */
	TypeObjects _vBillboardObjects;
	/** ビルボードオブジェクトを後で追加するためのコンテナ */
	TypeObjects _vPendingBillboardObjects;
	/** _v3DObjectsを回しているときはtrueにする */
	bool _updating;
	/** Del関数でオブジェクトが死んでいた場合_v3DObjectsからerase または_vBillboardObjectsからerase*/
	void DeleteObjects()
	{
		// _v3DObjectsをイテレータで回す( eraseがイテレータを要求しているため )
		for ( auto ite = _v3DObjects.begin(); ite != _v3DObjects.end(); )
		{
			if ( (*ite)->IsDead() )
			{
				ite = _v3DObjects.erase( ite );// これでobjectそのものも削除される
			}
			else
			{
				++ite;//次に進める
			}
		}
		// _vBillboardObjectsをイテレータで回す( eraseがイテレータを要求しているため )
		for ( auto ite = _vBillboardObjects.begin(); ite != _vBillboardObjects.end(); )
		{
			if ( (*ite)->IsDead() )
			{
				ite = _vBillboardObjects.erase( ite );// これでobjectそのものも削除される
			}
			else
			{
				++ite;//次に進める
			}
		}
	}
	/** _vPending3DObjects の中にあるものを _v3DObjects に追加 または_vPendingBillboardObjectsの中にあるものを_vBillboardObjectsに追加*/
	void AddPendingObjects()
	{
		// _vPending3DObjects -> _v3DObjects に追加
		_v3DObjects.insert( _v3DObjects.end(),make_move_iterator( _vPending3DObjects.begin() ),make_move_iterator( _vPending3DObjects.end() ) );
		// _vPending3DObjects をクリア
		_vPending3DObjects.clear();
		// _vPendingBillboardObjects -> _vBillboardObjects に追加
		_vBillboardObjects.insert( _vBillboardObjects.end(),make_move_iterator( _vPendingBillboardObjects.begin() ),make_move_iterator( _vPendingBillboardObjects.end() ) );
		// _vPendingBillboardObjects をクリア
		_vPendingBillboardObjects.clear();
	}
};

