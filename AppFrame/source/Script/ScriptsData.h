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
#include "../../../picojson/picojson.h"

class ScriptsData
{
public:
	ScriptsData() = default;
	ScriptsData( const ScriptsData& ) = default;
	ScriptsData( ScriptsData&& ) noexcept = default;

	virtual ~ScriptsData() = default;

	ScriptsData& operator=( const ScriptsData& right ) = default;
	ScriptsData& operator=( ScriptsData&& right ) noexcept = default;

	bool LoadJson( std::string filepath,std::string storyname,std::string filename = ".json" );
	bool WriteJson( std::string newfilename,std::string storyname );
	std::vector<std::string> GetScript( const unsigned int index,const std::string delimiter ) const;
	unsigned int GetScriptNum()  const;
	bool ScriptAdd( std::string Sclipts );
	bool ScriptDelete( int line );
	bool ScriptClear();
	std::string GetScriptLine( const unsigned int index ) const;
private:
	std::wstring ConvertUTF8ToWide( const std::string& utf8 ) const;
	std::string ConvertWideToUTF8( const std::wstring& utf16 )const;
	std::string ConvertWideToMultiByte( const std::wstring& utf16 ) const;
	std::wstring ConvertMultiByteToWide( const std::string& mbs )const;
	std::unique_ptr<std::vector<std::string>> scripts;
};