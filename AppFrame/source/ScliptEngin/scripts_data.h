/*****************************************************************//**
 * \file   scripts_data.h
 * \brief  スクリプトの読み込み定義
 *
 *
 * \author 真中先生
 * \date   August 2022
 *********************************************************************/

#pragma once

#include <tchar.h>
#include <vector>
#include <string>
#include <memory>
#include "picojson.h"

class ScriptsData
{
public:
	ScriptsData();
	ScriptsData(const ScriptsData&) = default;
	ScriptsData(ScriptsData&&) noexcept = default;

	virtual ~ScriptsData() = default;

	ScriptsData& operator=(const ScriptsData& right) = default;
	ScriptsData& operator=(ScriptsData&& right) noexcept = default;

	void LoadJson(std::string storyname);
	std::vector<std::string> GetScript(const unsigned int index) const;
	unsigned int GetScriptNum()  const;

private:
	std::string GetScriptLine(const unsigned int index) const;
	std::wstring ConvertUTF8ToWide(const std::string& utf8) const;
	std::string ConvertWideToMultiByte(const std::wstring& utf16) const;

	std::unique_ptr<std::vector<std::string>> scripts;
};