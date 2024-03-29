#pragma once
#include "appframe.h"
#include "../mode/ModeSpeakScript.h"
#include "ActorBaseSpeak.h"
class SpeakScriptObject:public ActorBaseSpeak
{
	using ActorSpeak = ActorBaseSpeak;
public:
	SpeakScriptObject( ApplicationBase& game,int layer,ModeSpeakScript& mode,int image_id,int music_id );
	virtual ~SpeakScriptObject();

	virtual void Initialize();/*ú»*/
	virtual bool Update();//
	virtual bool Draw();
	virtual bool DebugDraw();
private:

	std::vector<int> cg_ui;//uiæ
	int music_hundle;
};

