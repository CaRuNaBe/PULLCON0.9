#include "appframe.h"


class ApplicationGlobal
{
public:
	ApplicationGlobal();
	virtual ~ApplicationGlobal();

	bool Init();
	virtual bool GetIsEndSpeakScript()
	{
		return is_EndSpeakScript;
	}
	virtual void IsEndSpeakScript()
	{
		is_EndSpeakScript = true;
	}
	virtual void IsNotEndSpeakScript()
	{
		is_EndSpeakScript = false;
	}
public:
	bool is_EndSpeakScript;
}; 
// ���̃\�[�X��gGlobal���g����悤��
extern ApplicationGlobal    gGlobal;