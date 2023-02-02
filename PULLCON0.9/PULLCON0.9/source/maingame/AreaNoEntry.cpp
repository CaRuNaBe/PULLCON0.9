#include "AreaNoEntry.h"
AreaNoEntry::AreaNoEntry( ApplicationBase& game,ModeBase& mode,float _radius,float _height )
	:base(game,mode)
{
	height = _height;
	radius = _radius;
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
	return true;
};
bool AreaNoEntry::Draw()
{
	return true;
};