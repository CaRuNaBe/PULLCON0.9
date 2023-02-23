#pragma once
#include "CommandBase.h"
#include "../Math/math.h"
class CommandDrawTime final:public CommandBase
{
public:
	CommandDrawTime( unsigned int line,const std::vector<std::string>& script );
	CommandDrawTime( const CommandDrawTime& ) = default;
	CommandDrawTime( CommandDrawTime&& ) noexcept = default;

	virtual ~CommandDrawTime() = default;

	CommandDrawTime& operator=( CommandDrawTime const& right ) = default;
	CommandDrawTime& operator=( CommandDrawTime&& right ) = default;

	bool Check() override;

	inline int GetPosiX() const
	{
		return posi_x;
	}
	inline int GetPosiY() const
	{
		return posi_y;
	}

private:
	int posi_x;
	int posi_y;
};

