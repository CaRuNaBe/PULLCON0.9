#pragma once
#include "CommandBase.h"
class CommandDrawString final:public CommandBase
{
public:
	CommandDrawString( unsigned int line,const std::vector<std::string>& script );
	CommandDrawString( const CommandDrawString& ) = default;
	CommandDrawString( CommandDrawString&& ) noexcept = default;

	virtual ~CommandDrawString() = default;

	CommandDrawString& operator=( CommandDrawString const& right ) = default;
	CommandDrawString& operator=( CommandDrawString&& right ) = default;

	bool Check() override;

	inline int GetPosiX() const
	{
		return posi_x;
	}
	inline int GetPosiY() const
	{
		return posi_y;
	}
	inline int GetStringHandle() const
	{
		return string_handle;
	}
	inline unsigned int GetStringColor() const
	{
		return string_color;
	}
	inline std::string GetString() const
	{
		return script[8];
	}
private:
	int posi_x;
	int posi_y;
	int string_handle;
	unsigned int string_color;
};

