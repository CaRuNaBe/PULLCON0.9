/*****************************************************************//**
 * \file   ModeResourceRoad.cpp
 * \brief
 *
 * \author ���������Y
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
};

ModeResourceRoad::~ModeResourceRoad()
{
};
bool ModeResourceRoad::Initialize()
{
	return true;
};
	// �X�V
bool ModeResourceRoad::Update()
{
	ModeBase::Update();

	return true;
};
	// �`��
bool ModeResourceRoad::Draw()
{
	ModeBase::Draw();
	return true;
};