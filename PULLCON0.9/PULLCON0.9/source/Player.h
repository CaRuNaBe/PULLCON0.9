#pragma once
#include "appframe.h"
#include "ActorBase.h"

class Player : public ActorBase {
	typedef ActorBase base;
public:
	Player();
	virtual ~Player();
	virtual Type GetType() { return Type::kPlayer; }

	virtual void Init();
	virtual void Update(ApplicationBase& game);
	virtual void Draw(ApplicationBase& game);

protected:


};
