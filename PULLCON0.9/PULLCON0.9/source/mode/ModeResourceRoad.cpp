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
	: GameBase( game,layer )
{
	Initialize();
};

ModeResourceRoad::~ModeResourceRoad()
{
};
bool ModeResourceRoad::Initialize()
{
	return true;
};
	// çXêV
bool ModeResourceRoad::Update()
{
	return true;
};
	// ï`âÊ
bool ModeResourceRoad::Draw()
{
	return true;
};

bool ModeResourceRoad::DebugDraw()
{
	return true;
};
