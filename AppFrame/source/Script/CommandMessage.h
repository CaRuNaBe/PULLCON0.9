#pragma once
#include "CommandBase.h"
#include <string>
#include "../Math/math.h"
class CommandMessage final: public CommandBase
{
public:
	CommandMessage( unsigned int line,const std::vector<std::string>& script );
	CommandMessage( const CommandMessage& ) = default;
	CommandMessage( CommandMessage&& ) noexcept = default;

	virtual ~CommandMessage() = default;

	CommandMessage& operator=( const CommandMessage& right ) = default;
	CommandMessage& operator=( CommandMessage&& right ) noexcept = default;

	bool Check() override;


	std::string WhoSpeak() const
	{
		return script[1];
	}

	std::string GetMessageA() const
	{
		return script[2];
	}

	void SetPosition(math::Vector2 set_vec)
	{
		posi.Set( set_vec );
	}
	math::Vector2 GetPosition()
	{
		return posi;
	}
protected:
	math::Vector2 posi;
};
