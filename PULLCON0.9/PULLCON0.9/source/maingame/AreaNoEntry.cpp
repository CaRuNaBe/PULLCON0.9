#include "AreaNoEntry.h"
AreaNoEntry::AreaNoEntry(ApplicationBase& game, int layer, ModeMainGame& mode)
	:ActorMainGame(game, layer, mode)
{
	Initialize();
};

AreaNoEntry::~AreaNoEntry()
{};

void AreaNoEntry::Initialize()
{
	ActorMainGame::Initialize();
};

bool AreaNoEntry::Update()
{
	ActorMainGame::Update();
	_collision._fRadius = _fRadius;
	UpdateCollision();
	return true;
};

bool AreaNoEntry::Draw()
{
	ActorMainGame::Draw();
	if (!_mode._dbgCollisionDraw)
	{
		// ƒRƒŠƒWƒ‡ƒ“•`‰æ
		Vector4 color = { 255, 0, 255 };
		DrawCollisionObject(color);
	}
	return true;
};