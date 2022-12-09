#pragma once
#include	<unordered_map>
#include<string>
// リソース管理サーバ
// すべて静的メンバで構成する
struct DIVGRAPH
{
	int		AllNum;
	int* handle;
};
using ResourceMap = std::unordered_map<std::string,int>;
using DivGraphMap = std::unordered_map<std::string,DIVGRAPH>;

class ResourceServer
{
public:
	static void	Init();
	static void Release();
	static void	ClearGraph();

	static int LoadGraph(std::string FileName);

	static int LoadDivGraph(std::string FileName,int AllNum,int XNum,int YNum,int XSize,int YSize,int* HandleBuf);

	static int LoadSoundMem(std::string FileName);

private:
	static DivGraphMap _mapDivGraph;
	static ResourceMap _mapGraph;
	static ResourceMap _mapSound;
};

