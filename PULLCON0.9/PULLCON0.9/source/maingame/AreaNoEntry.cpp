#include "AreaNoEntry.h"
AreaNoEntry::AreaNoEntry( float _radius,float _height )
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
bool AreaNoEntry::Update( ApplicationBase& game,ModeBase& mode )
{
	return true;
};
bool AreaNoEntry::Draw( ApplicationBase& game,ModeBase& mode )
{
	return true;
};