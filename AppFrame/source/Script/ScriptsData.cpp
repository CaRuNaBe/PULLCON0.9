/*****************************************************************//**
 * \file   scripts_data.cpp
 * \brief  スクリプトの読み込み実装
 *
 *
 * \author 真中先生
 * \date   August 2022
 *********************************************************************/

#include "ScriptsData.h"
#include "ScriptsString.h"
#include <windows.h>
#include <fstream>
#include "picojson.h"

namespace
{
	constexpr auto EMPTY_STR = _T( "" );
	constexpr auto EMPTY_WSTR = L"";
	constexpr auto DELIMITER = _T( "," );
}
//!
//! @fn bool ScriptsData::LoadJson(const TCHAR* path)
//! @brief スクリプト用 Json ファイルの読込
//! @param[in] path パス付のスクリプト用 Json ファイル名
//! @return 処理の成否
//! @details Json ファイルは BOM 無し UTF-8 を想定しています。
//! 基本的には付属のエクセル(amg_scripts.xlsm)より出力される事を想定しています。
//! 本プロジェクトが使用している DX ライブラリの指定で
//! VisualStudio の文字コード指定はマルチバイト文字となっており
//! 読込時は Json(UTF-8) -> ユニコード(UTF-16) -> マルチバイト文字
//! の様に文字コードの変換を行います。
//!
bool ScriptsData::LoadJson( std::string filepath,std::string storyname,std::string filename  )
{
	// UTF-8 BOM無し Json file
	std::ifstream ifs( filepath );
	if ( scripts == nullptr )
	{
		scripts.reset( new std::vector<std::string>() );
	}
	//もしなかった場合新規作成
	if ( !ifs )
	{
		std::ofstream writing_file;
		writing_file.open( filename,std::ios::out );
		picojson::array datalist;

		picojson::object license;
		license.insert( std::make_pair( storyname,picojson::value( datalist ) ) );

		picojson::array loot;
		loot.push_back( picojson::value( license ) );
		std::cout << picojson::value( loot ) << std::endl;
		writing_file << picojson::value( loot ).serialize() << std::endl;
		writing_file.close();
	}
	else
	{
		picojson::value json_value;

		ifs >> json_value;

		const auto& err = picojson::get_last_error();

		if ( !err.empty() )
		{
			return false;
		}
		std::cout << picojson::value( json_value ) << std::endl;
		auto& root = json_value.get<picojson::array>();
		auto& object = root[0].get<picojson::object>();
		const auto& array = object[storyname].get<picojson::array>();

		// UTF-8 -> Wide(UTF-16) -> MultiByte と文字コードを変換しながらスクリプト文字を取得
		for ( auto i = array.begin(); i != array.end(); ++i )
		{
			const auto& utf8 = (*i).get<std::string>();
			const auto utf16 = ConvertUTF8ToWide( utf8 );
			const auto mbs = ConvertWideToMultiByte( utf16 );

			scripts->emplace_back( mbs );
		}

	}
	ifs.close();
	return true;
}

bool ScriptsData::WriteJson( std::string newfilename,std::string storyname )
{
	std::ofstream writing_file;
	writing_file.open( newfilename,std::ios::out );

	picojson::array datalist;
	for ( auto i = scripts->begin(); i != scripts->end(); ++i )
	{
		const auto& mbs = *i;//マルチバイト文字取得
		const auto utf16 = ConvertMultiByteToWide( mbs );//マルチバイト文字からUTF-16
		const auto utf8 = ConvertWideToUTF8( utf16 );//utf-16からutf-8
		datalist.push_back( picojson::value( utf8 ) );
	}

	picojson::object license;
	license.insert( std::make_pair( storyname,picojson::value( datalist ) ) );

	picojson::array loot;
	loot.push_back( picojson::value( license ) );

	writing_file << picojson::value( loot ).serialize() << std::endl;
	writing_file.close();
	return true;
}
//!
//! @fn std::wstring ScriptsData::ConvertUTF8ToWide(const std::string& utf8) const
//! @brief UTF-8 文字コードの std::string を std::wstring(UTF-16) に変換する
//! @param[in] utf8 UTF-8 文字コードの std::string
//! @return UTF-16 文字コードの std::wstring
//!
std::wstring ScriptsData::ConvertUTF8ToWide( const std::string& utf8 ) const
{
	if ( utf8.empty() )
	{
		return EMPTY_WSTR;
	}

	const auto in_length = static_cast<int>(utf8.length());
	const auto out_length = MultiByteToWideChar( CP_UTF8,0,utf8.c_str(),in_length,0,0 );

	if ( out_length <= 0 )
	{
		return EMPTY_WSTR;
	}

	std::vector<wchar_t> buffer( out_length );

	MultiByteToWideChar( CP_UTF8,0,utf8.c_str(),in_length,&(buffer[0]),out_length );

	std::wstring utf16( buffer.begin(),buffer.end() );

	return std::move( utf16 );
}

std::string ScriptsData::ConvertWideToUTF8( const std::wstring& utf16 )const
{
	if ( utf16.empty() )
	{
		return EMPTY_STR;
	}

	const auto in_length = static_cast<int>(utf16.length());
	const auto out_length = WideCharToMultiByte( CP_UTF8,0,utf16.c_str(),in_length,0,0,0,0 );

	if ( out_length <= 0 )
	{
		return EMPTY_STR;
	}

	std::vector<char> buffer( out_length );

	WideCharToMultiByte( CP_UTF8,0,utf16.c_str(),in_length,&(buffer[0]),out_length,0,0 );

	std::string mbs( buffer.begin(),buffer.end() );

	return std::move( mbs );
}
//!
//! @fn std::string ScriptsData::ConvertWideToMultiByte(const std::wstring& utf16) const
//! @brief std::wstring(UTF-16) をマルチバイト文字コードの std::string に変換する
//! @param[in] utf16 UTF-16 文字コードの std::wstring
//! @return マルチバイト文字コードの std::string
//!
std::string ScriptsData::ConvertWideToMultiByte( const std::wstring& utf16 ) const
{
	if ( utf16.empty() )
	{
		return EMPTY_STR;
	}

	const auto in_length = static_cast<int>(utf16.length());
	const auto out_length = WideCharToMultiByte( CP_ACP,0,utf16.c_str(),in_length,0,0,0,0 );

	if ( out_length <= 0 )
	{
		return EMPTY_STR;
	}

	std::vector<char> buffer( out_length );

	WideCharToMultiByte( CP_ACP,0,utf16.c_str(),in_length,&(buffer[0]),out_length,0,0 );

	std::string mbs( buffer.begin(),buffer.end() );

	return std::move( mbs );
}

std::wstring ScriptsData::ConvertMultiByteToWide( const std::string& mbs )const
{
	if ( mbs.empty() )
	{
		return EMPTY_WSTR;
	}

	const auto in_length = static_cast<int>(mbs.length());
	const auto out_length = MultiByteToWideChar( CP_ACP,0,mbs.c_str(),in_length,0,0 );

	if ( out_length <= 0 )
	{
		return EMPTY_WSTR;
	}

	std::vector<wchar_t> buffer( out_length );

	MultiByteToWideChar( CP_ACP,0,mbs.c_str(),in_length,&(buffer[0]),out_length );

	std::wstring utf16( buffer.begin(),buffer.end() );

	return std::move( utf16 );
}
//!
//! @fn unsigned int ScriptsData::GetScriptNum()  const
//! @brief 読み込んだ Json のスクリプト数を返す
//! @return スクリプト数
//! @details スクリプトはインタプリタ方式で 1 スクリプト 1 行となります。
//!
unsigned int ScriptsData::GetScriptNum()  const
{
	if ( scripts == nullptr )
	{
		return 0;
	}

	return static_cast<unsigned int>(scripts->size());
}

//!
//! @fn std::string ScriptsData::GetScriptLine(const unsigned int index) const
//! @brief 指定行のスクリプトを返す
//! @param[in] index スクリプト内の指定行数
//! @return スクリプト文字
//! @details エラー時は空文字が返ります。
//!
std::string ScriptsData::GetScriptLine( const unsigned int index ) const
{
	const auto size = GetScriptNum();

	if ( size <= 0 || size <= index )
	{
		return EMPTY_STR;
	}

	return (*scripts)[index];
}

//!
//! @fn std::vector<std::string> ScriptsData::GetScript(const unsigned int index) const
//! @brief 指定行のスクリプトをパラメータに分解して返す
//! @param[in] index スクリプト内の指定行数
//! @return 分解されたスクリプト文字
//! @details エラー時は空文字が返ります。
//! スクリプトはカンマ(',')で区切られており
//! "コマンド文字, パラメータ1, パラメータ2, ..."
//! (パラメータ数はコマンドにより違う)
//! の様なフォーマットになっています。
//! それを ',' で区切った vector の string 配列として返します。
//!
std::vector<std::string> ScriptsData::GetScript( const unsigned int index ) const
{
	const auto line = GetScriptLine( index );

	return string::Split( line,DELIMITER );
}

bool ScriptsData::ScriptAdd( std::string& Sclipts )
{
	scripts->emplace_back( Sclipts );
	return true;
};
bool ScriptsData::ScriptDelete( int line )
{
	scripts->erase( scripts->begin() + line );
	return true;
};
bool ScriptsData::ScriptClear()
{
	scripts->clear();
	return true;
};

