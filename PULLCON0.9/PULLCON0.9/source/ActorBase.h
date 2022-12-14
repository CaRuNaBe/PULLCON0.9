#pragma once
#include "appframe.h"

class ActorBase : public ObjectBase
{
	typedef ObjectBase base;
public:
	ActorBase();
	virtual ~ActorBase();

	enum Type {  // ��ʂ̗񋓌^
		kBase,     // 0 �A�N�^�[
		kPlayer    // 1 �v���C���[
	};
	virtual Type GetType() = 0;

	virtual void Init();
	virtual void Update(ApplicationBase& game);
	virtual void Draw(ApplicationBase& game);

public:
	math::vector4 _vPos;
};
