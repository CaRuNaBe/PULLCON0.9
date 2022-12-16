#pragma once
#include "appframe.h"

class ActorBase : public ObjectBase
{
	typedef ObjectBase base;
public:
	ActorBase();
	virtual ~ActorBase();

	enum Type {  // 種別の列挙型
		kBase,     // 0 アクター
		kPlayer    // 1 プレイヤー
	};
	virtual Type GetType() = 0;

	virtual void Init();
	virtual bool Update(ApplicationBase& game);
	virtual bool Draw(ApplicationBase& game);

public:
	math::vector4 _vPos;
};

