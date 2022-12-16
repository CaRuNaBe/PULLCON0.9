#pragma once
/*****************************************************************//**
 * \file   ScliptFlagManager.h
 * \brief スクリプト操作フラグクラス
 *
 * \author 阿部健太郎
 * \date   December 2022
 *********************************************************************/
class ScliptFlagManager
{
public:
	ScliptFlagManager();
	~ScliptFlagManager();
	bool GetisEndsclipt()
	{
		return isEndsclipt;
	}
	bool GetisLoadend()
	{
		return isLoadend;
	}
	bool GetisBlackbackground()
	{
		return isBlackbackground;
	}
	void SetisEndsclipt(const bool Endsclipt)
	{
		isEndsclipt = Endsclipt;
	}
	void SetisLoadend(const bool Loadend)
	{
		isLoadend = Loadend;
	}
	void SetisBlackbackground(const bool Blackbackground)
	{
		isBlackbackground = Blackbackground;
	}
private:
	bool isEndsclipt;//スクリプトを終わらせるときtrue
	bool isLoadend;//スクリプトを開いたと同時にローディング画面を開いた時に使用ローディングが終わったらtrue
	bool isBlackbackground;//スクリプトを開いている時後ろの画面を表示管理フラグtrueの時後ろ画面は映らない
};

