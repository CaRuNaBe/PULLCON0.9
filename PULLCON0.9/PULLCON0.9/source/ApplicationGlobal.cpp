
#include "appframe.h"
#include "ApplicationGlobal.h"

// ����
ApplicationGlobal		gGlobal;

ApplicationGlobal::ApplicationGlobal()
{
	is_EndSpeakScript = false;
}

ApplicationGlobal::~ApplicationGlobal()
{
}

bool ApplicationGlobal::Init()
{
	is_EndSpeakScript = false;

	return true;
}
