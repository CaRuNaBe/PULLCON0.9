#pragma once
#include "CommandBase.h"

class CommandDrawRect final:
	public CommandBase
{
public:
	CommandDrawRect( unsigned int line,const std::vector<std::string>& script );
	CommandDrawRect( const CommandDrawRect& ) = default;
	CommandDrawRect( CommandDrawRect&& ) noexcept = default;

	virtual ~CommandDrawRect() = default;

	CommandDrawRect& operator=( CommandDrawRect const& right ) = default;
	CommandDrawRect& operator=( CommandDrawRect&& right ) = default;

	bool Check() override;

	inline unsigned int GetRectColor() const
	{
		return color;
	}
	inline int GetPosiX1() const
	{
		return posi_x1;
	}
	inline int GetPosiY1() const
	{
		return posi_y1;
	}
	inline int GetPosiX2() const
	{
		return posi_x2;
	}
	inline int GetPosiY2() const
	{
		return posi_y2;
	}
private:
	unsigned int color;
	int posi_x1;
	int posi_y1;
	int posi_x2;
	int posi_y2;
};

