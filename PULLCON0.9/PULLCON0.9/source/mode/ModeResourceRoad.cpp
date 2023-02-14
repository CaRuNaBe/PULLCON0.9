/*****************************************************************//**
 * \file   ModeResourceRoad.cpp
 * \brief
 *
 * \author à¢ïîåíëæòY
 * \date   September 2022
 *********************************************************************/
#include "ModeResourceRoad.h"

#include<dxlib.h>

namespace
{
	constexpr auto DELAYTIME = 3;
}

ModeResourceRoad::ModeResourceRoad( ApplicationBase& game,int layer )
	: ModeBase( game,layer )
{
	Initialize();
};

ModeResourceRoad::~ModeResourceRoad()
{
};
bool ModeResourceRoad::Initialize()
{
	base::Initialize();
	return true;
};
	// çXêV
bool ModeResourceRoad::Update()
{
	ModeBase::Update();

	return true;
};
	// ï`âÊ
bool ModeResourceRoad::Draw()
{
	ModeBase::Draw();
	return true;
};

bool ModeResourceRoad::DebugDraw()
{
	base::DebugDraw();
	return true;
};
