#pragma once
#include "appframe.h"

class Player : public ObjectBase {
	typedef ObjectBase base;
public:
	Player();
	virtual ~Player();
	virtual void Init();
	virtual void Update(ApplicationBase& game);
	virtual void Draw(ApplicationBase& game);

protected:


};
