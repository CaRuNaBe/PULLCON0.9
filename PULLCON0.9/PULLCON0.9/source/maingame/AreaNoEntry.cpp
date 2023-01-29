#include "AreaNoEntry.h"
AreaNoEntry::AreaNoEntry( int _radius,int _height )
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