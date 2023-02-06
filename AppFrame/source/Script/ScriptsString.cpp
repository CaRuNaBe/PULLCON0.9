#include "ScriptsString.h"

namespace string
{
	bool ToInt( const std::string& str,int& integer )
	{
		auto result = true;
		try
		{
			integer = std::stoi( str );
		}
		catch ( ... )
		{
			result = false;
		}
		return result;
	}

	bool ToFloat( const std::string& str,float& floatnum )
	{
		auto result = true;
		try
		{
			floatnum = std::stof( str );
		}
		catch ( ... )
		{
			result = false;
		}
		return result;
	}

	std::vector<std::string> Split( const std::string& str,const std::string& delimiter )
	{
		size_t first = 0;
		auto last = str.find_first_of( delimiter );
		std::vector<std::string> split;

		while ( first < str.size() )
		{
			const std::string subStr( str,first,last - first );

			split.emplace_back( subStr );

			first = last + delimiter.length();
			last = str.find_first_of( delimiter,first );

			if ( last == std::string::npos )
			{
				last = str.size();
			}
		}
		return split;
	}
	std::string Combine( std::vector<std::string>& script,const std::string& delimiter )
	{
		auto script_size = script.size();
		std::string str;
		for ( int i = 0; i < script_size; i++ )
		{
			str += script[i];
			if ( i < script_size - 1 )
			{
				str += delimiter;
			}
		}
		return str;
	}
}