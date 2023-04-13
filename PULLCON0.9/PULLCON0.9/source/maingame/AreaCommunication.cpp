#include "AreaCommunication.h"
#include "../mode/ModeSpeakScript.h"
#include "../ApplicationGlobal.h"

AreaCommunication::AreaCommunication(ApplicationBase& game, int layer, ModeMainGame& mode, const std::string& storyname)
	:ActorMainGame(game, layer, mode)
	,storyname(storyname)
{
	Initialize();
}

AreaCommunication::~AreaCommunication()
{}

void AreaCommunication::Initialize()
{
	ActorMainGame::Initialize();
}

bool AreaCommunication::Update()
{
	ActorMainGame::Update();

	_collision._fRadius = _fRadius * _fScale;
	for (auto&& obje : _mode.GetObjectServer3D().GetObjects())
	{
		if ((obje->GetType() == ActorMainGame::Type::kPlayer))
		{
			if (IsHitObject(*obje))
			{
				if (gGlobal.GetIsEndSpeakScript())
				{
					gGlobal.IsNotEndSpeakScript();
					PlaySoundMem(gGlobal._se["comm_start"], DX_PLAYTYPE_BACK);
					auto story = std::make_shared<ModeSpeakScript>(_game, 30, storyname);
					_game.GetModeServer()->Add(story);

					_mode.GetObjectServer3D().Del(*this);
				}
				break;
			}
		}
	}
	UpdateCollision();
	return true;
}

bool AreaCommunication::Draw()
{
	ActorMainGame::Draw();
	// ƒRƒŠƒWƒ‡ƒ“•`‰æ
#if _DEBUG
	Vector4 color = { 255, 255, 255 };
	DrawCollision(color);
#endif
	return true;
}