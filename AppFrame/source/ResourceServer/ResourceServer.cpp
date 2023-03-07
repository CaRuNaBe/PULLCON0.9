/*
** リソースサーバ
*/

#include "DxLib.h"
#include "ResourceServer.h"

// 静的メンバ実体
ResourceMap	ResourceServer::_mapGraph;
DivGraphMap ResourceServer::_textures;
DIVGRAPHMAP	ResourceServer::_mapDivGraph;
ResourceMap	ResourceServer::_mapSound;
ResourceMap	ResourceServer::_mapMV1Model;

void    ResourceServer::Init()
{
	_mapGraph.clear();
	_textures.clear();
	_mapDivGraph.clear();
	_mapSound.clear();
	_mapMV1Model.clear();
}

void    ResourceServer::Release()
{
	ClearGraph();
}

void	ResourceServer::ClearGraph()
{
	// すべてのデータの削除をする
	for ( auto itr = _mapGraph.begin(); itr != _mapGraph.end(); itr++ )
	{
		DeleteGraph( itr->second );
	}
	_mapGraph.clear();

	for (auto&& dgm : _textures) {
		for (auto gh : dgm.second._handles) {
			DeleteGraph(gh);
		}
	}
	_textures.clear();

	for ( auto itr = _mapDivGraph.begin(); itr != _mapDivGraph.end(); itr++ )
	{
		for ( int i = 0; i < itr->second.AllNum; i++ )
		{
			DeleteGraph( itr->second.handle[i] );
		}
		delete[] itr->second.handle;
	}
	_mapDivGraph.clear();

	for ( auto itr = _mapSound.begin(); itr != _mapSound.end(); itr++ )
	{
		DeleteSoundMem( itr->second );
	}
	_mapSound.clear();

	for ( auto itr = _mapMV1Model.begin(); itr != _mapMV1Model.end(); itr++ )
	{
		MV1DeleteModel( itr->second );
	}
	_mapMV1Model.clear();
}

int		ResourceServer::LoadGraph( std::string FileName )
{
	// キーの検索
	auto itr = _mapGraph.find( FileName );
	if ( itr != _mapGraph.end() )
	{
		// キーがあった
		return itr->second;
	}
	// キーが無かった
	int cg = ::LoadGraph( FileName.c_str() );     // DXLIBのAPIを呼ぶので、::を先頭に付け、このクラスの同じ名前の関数と区別する
	// キーとデータをmapに登録
	_mapGraph[FileName] = cg;

	return cg;
}

void ResourceServer::LoadTextures(const DivGraphMap& divGraphMap) {
	for (auto&& dgm : divGraphMap) {
		auto& key = dgm.first;
		// キーを検索する
		auto it = _textures.find(key);
		if (it != _textures.end()) {
			continue;
		}
		// DivGraphをコピーする
		auto dg = dgm.second;
		auto allNum = dg._xNum * dg._yNum;
		dg._handles.resize(allNum);
		// 画像の分割読み込み
		LoadDivGraph(dg._filename.c_str(),
			allNum,
			dg._xNum, dg._yNum,
			dg._xSize, dg._ySize, dg._handles.data());
		// DivGraphMapに追加する
		_textures.emplace(key.c_str(), dg);
	}
}

int ResourceServer::GetHandles(const std::string& key, int no) {
	auto it = _textures.find(key);
	if (it == _textures.end()) {
		return -1;
	}
	auto gh = it->second._handles.at(no);
	return gh;
}
bool ResourceServer::GetHandles(const std::string& key, std::vector<int>& handles) {
	auto it = _textures.find(key);
	if (it == _textures.end()) {
		return false;
	}
	handles.resize(it->second._handles.size());
	handles = it->second._handles;
	return true;
}
int ResourceServer::GetAllNum(const std::string& key) {
	auto it = _textures.find(key);
	if (it == _textures.end()) {
		return -1;
	}
	return it->second._xNum * it->second._yNum;
}

const DivGraph& ResourceServer::GetDivGraph(const std::string& key) {
	auto it = _textures.find(key);
	return it->second;
}

int		ResourceServer::LoadDivGraph( std::string FileName,int AllNum,int XNum,int YNum,int XSize,int YSize,int* HandleBuf )
{
	// キーの検索
	auto itr = _mapDivGraph.find( FileName );
	if ( itr != _mapDivGraph.end() )
	{
		// キーがあった
		// データをコピー
		for ( int i = 0; i < itr->second.AllNum; i++ )
		{
			HandleBuf[i] = itr->second.handle[i];
		}
		return 0;
	}
	// キーが無かった
	// まずはメモリを作成する
	int* hbuf = new int[AllNum];
	int err = ::LoadDivGraph( FileName.c_str(),AllNum,XNum,YNum,XSize,YSize,hbuf );     // DXLIBのAPIを呼ぶので、::を先頭に付け、このクラスの同じ名前の関数と区別する
	if ( err == 0 )
	{
		// 成功
		// キーとデータをmapに登録
		_mapDivGraph[FileName].AllNum = AllNum;
		_mapDivGraph[FileName].handle = hbuf;
		// データをコピー
		for ( int i = 0; i < AllNum; i++ )
		{
			HandleBuf[i] = hbuf[i];
		}
	}

	return err;
}

int		ResourceServer::LoadSoundMem( std::string FileName )
{
	// キーの検索
	auto itr = _mapSound.find( FileName );
	if ( itr != _mapSound.end() )
	{
		// キーがあった
		return itr->second;
	}
	// キーが無かった
	// DXLIBのAPIを呼ぶので、::を先頭に付け、このクラスの同じ名前の関数と区別する
	int snd = ::LoadSoundMem( FileName.c_str() );
	// キーとデータをmapに登録
	_mapSound[FileName] = snd;

	return snd;
}

int ResourceServer::LoadMV1Model( std::string FileName )
{
	int cg = 0;
	if ( _mapMV1Model.count( FileName ) == 0 )
	{
			//キーがなかった
		int cg = ::MV1LoadModel( FileName.c_str() );
		_mapMV1Model[FileName] = cg;
	}
	cg = MV1DuplicateModel( _mapMV1Model[FileName] );
	return cg;
}