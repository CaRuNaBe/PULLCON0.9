#include "AreaNoEntry.h"
AreaNoEntry::AreaNoEntry( ApplicationBase& game,ModeBase& mode )
	:base(game,mode)
{
	Init();
};
AreaNoEntry::~AreaNoEntry()
{
};

void AreaNoEntry::Init()
{
};
bool AreaNoEntry::Update()
{
	_collision._fRadius = _fRadius * _fScale;
	UpdateCollision();
	return true;
};
bool AreaNoEntry::Draw()
{
	// コリジョン描画
	vector4 color = {255, 0, 255};
	DrawCollision( color );
	return true;
};