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
	std::shared_ptr<ScriptsData> image_pass_date;
	std::shared_ptr<ScriptsData> music_pass_date;
	std::shared_ptr<ScriptsData> object_pass_date;
};
// ���̃\�[�X��gGlobal���g����悤��
extern ApplicationGlobal gGlobal;