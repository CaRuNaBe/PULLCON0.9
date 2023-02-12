#include<algorithm>
#include "DxLib.h"
#include "ModeBase.h"
#include "ModeServer.h"

ModeServer::ModeServer(ApplicationBase& game)
	:_updating(false)
{}

ModeServer::~ModeServer()
{
	Clear();
}

void ModeServer::Clear()
{
	if(_updating)
	{
		for(auto&& mode : _vModes)
		{
			mode->Dead();
		}
	}
	else
	{
		_vModes.clear();
	}
}

void	ModeServer::Add(ModeBasePtr mode)
{
	if(_updating)
	{
		_vPendingModes.push_back(mode);
	}
	else
	{
		_vModes.push_back(mode);
	}
}

void	ModeServer::AddPendingModes()
{
	// _vPendingModes -> _vModes に追加
	_vModes.insert(
		_vModes.end(),
		make_move_iterator(_vPendingModes.begin()),
		make_move_iterator(_vPendingModes.end())
	);
	// _vPendingModes をクリア
	_vPendingModes.clear();
}

void	ModeServer::Del(ModeBase& mode)
{
	mode.Dead();
}

void	ModeServer::DeleteModes()
{
	// コンテナをイテレータで回す( eraseがイテレータを要求しているため )
	for(auto ite = _vModes.begin(); ite != _vModes.end(); )
	{
		if((*ite)->IsDead())
		{
			ite = _vModes.erase(ite);		// これでobjectそのものも削除される
		}
		else
		{
			++ite;
		}
	}

}



// 更新
bool ModeServer::Update()
{

	_updating = true;
	for(auto&& mode : _vModes)
	{
		if(mode->GetUpdateSkip())
		{
			continue;
		}
		mode->Update();
	}

	// レイヤーによるソート
	std::sort(_vModes.begin(),_vModes.end(),[](const ModeBasePtr ch1,const ModeBasePtr ch2)
	{
		return ch1->GetLayer() < ch2->GetLayer();
	});

	_updating = false;
	AddPendingModes();
	DeleteModes();	// 削除予約されたオブジェクトを削除する
	return true;
}



// 描画
bool ModeServer::Draw()
{
	for(auto&& mode : _vModes)
	{
		if(mode->GetDrawSkip())
		{
			continue;
		}
		mode->Draw();
	}
	return true;
}

