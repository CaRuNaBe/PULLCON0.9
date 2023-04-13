#include "AreaSupply.h"
#include "../ApplicationGlobal.h"
#include "../mode/ModeMainGame.h"
namespace
{
	constexpr int SUPPLY_ID = 37;
}
AreaSupply::AreaSupply(ApplicationBase& game, int layer, ModeMainGame& mode, float _radius)
	:ActorMainGame(game, layer, mode)
{
	_handle = ResourceServer::LoadMV1Model(gGlobal.object_pass_date->GetScriptLine(SUPPLY_ID));
	Initialize();
	_fRadius = _radius;
}

AreaSupply::~AreaSupply()
{
	MV1DeleteModel(_handle);
}

void AreaSupply::Initialize()
{
	ActorMainGame::Initialize();
}

bool AreaSupply::Update()
{
	ActorMainGame::Update();

	for (auto&& obje : _mode.GetObjectServer3D().GetObjects())
	{
		if (obje->GetType() == Type::kPlayer)
		{
			if (Intersect(obje->_collision, _collisionEvent))
			{
				if (!(CheckSoundMem(gGlobal._se["se_supply"])))
				{
					PlaySoundMem(gGlobal._se["se_supply"], DX_PLAYTYPE_BACK);
				}

				_event = true;
				if (_cnt % 10 == 0)
				{
					obje->_iFuel++;
					if (obje->_iFuel > 100)
					{
						obje->_iFuel = 100;
					}
				}
			}
			break;
		}
	}

	_collisionEvent._fRadius = _fRadius * _fScale;
	_vEvent = _vPos;
	UpdateCollision();  // コリジョン更新

	return true;
}

bool AreaSupply::Draw()
{
	ActorMainGame::Draw();
	// モデル拡大
	MV1SetScale(_handle, VGet(_fScale, _fScale, _fScale));
	// モデル移動
	MV1SetPosition(_handle, ToDX(_vPos));
	// ライティング計算
	// モデル描画
	SetUseLighting(FALSE);
	MV1DrawModel(_handle);
	SetUseLighting(TRUE);

	// コリジョン描画
	if (!_mode._dbgCollisionDraw)
	{
		Vector4 color = { 255, 255, 255 };
		DrawCollisionEvent(color);
		if (_event)
		{
			color = { 0, 255, 0 };
			DrawCollisionEvent(color);
		}
	}

	return true;
}
