#pragma once
#include "appframe.h"
class SpeakScriptObject:
	public ActorBaseSpeak
{
	using ActorSpeak = ActorBaseSpeak;
public:
	SpeakScriptObject( ApplicationBase& game,ModeBase& mode,int image_id,int music_id );
	~SpeakScriptObject();

	void	Init();//������
	bool	Update();
	bool	Draw();
private:
	std::vector<int> cg_ui;//ui�摜
	int music_hundle;
};

