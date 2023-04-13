#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
#include "../ApplicationGlobal.h"
ActorMainGame::ActorMainGame(ApplicationBase& game, int layer, ModeMainGame& mode)
  :GameBase(game, layer)
  , _mode(mode)
{
  Initialize();
}

ActorMainGame::~ActorMainGame()
{}

void ActorMainGame::Initialize()
{
  _vPos = { 0.f, 0.f ,0.f };
  _vEvent = { 0.f, 0.f ,0.f };
  _vRelation = { 0.f, 0.f ,0.f };
  _vTarget = { 0.f, 0.f ,0.f };
  _vDir = { 0.f, 0.f ,0.f };
  _vVelocity = { 0.f, 0.f ,0.f };

  _collision = { {0.f,0.f,0.f},0.f };
  _collisionEvent = { {0.f,0.f,0.f},0.f };
  _collisionSearch = { {0.f,0.f,0.f},0.f };

  _iFuel = 0;
  _iLife = 0;
  _iDamage = 0;
  _iPieces = 0;
  _iPart = 0;
  _iType = 0;
  _fSpeed = 0.f;
  _fScale = 1.f;
  _fRotatX = 0.f;
  _fRotatY = 0.f;
  _coll = true;
  _overlap = false;
  _event = false;
  _pull = false;
  _finish = false;
  _fire = false;
  _synchronize = false;
  _takeIn = false;
  _cnt = 0;
  _CT = 0;
  _ST = 0;

  _fRadius = 0.0f;
}

bool ActorMainGame::Update()
{
  _overlap = false;
  _event = false;
  _fire = false;

  _cnt++;
  if (_CT > 0)
  {
    _CT--;
  }
  if (_ST > 0)
  {
    _ST--;
  }
  return true;
}

void ActorMainGame::UpdateCollision()
{
  _collision._vCenter = _vPos;
  _collisionSearch._vCenter = _vPos;
  _collisionEvent._vCenter = _vEvent;
}

bool ActorMainGame::IsHitObject(ActorMainGame& object)
{
  if (_coll && object._coll == true)
  {
    // Sphereで当たり判定
    if (Intersect(object.GetCollision(), _collision))
    {
      return true;
    }
  }
  return false;
}

bool ActorMainGame::IsHitEvent(ActorMainGame& object)
{
  if (_coll && object._coll == true)
  {
    // Sphereで当たり判定
    if (Intersect(object.GetCollisionEvent(), _collision))
    {
      return true;
    }
  }
  return false;
}

bool ActorMainGame::IsSearch(ActorMainGame& object)
{
  // Sphereで当たり判定
  if (Intersect(object.GetCollision(), _collisionSearch))
  {
    return true;
  }
  return false;
}

bool ActorMainGame::Draw()
{
  return true;
}

bool ActorMainGame::DebugDraw()
{
  return true;
}

void ActorMainGame::DrawCollision(vector4 color)
{
#if _DEBUG
  // ライティング計算
  SetUseLighting(FALSE);
  _collision.Draw(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
  SetUseLighting(TRUE);
#endif
}

void ActorMainGame::DrawCollisionEvent(vector4 color)
{
#if _DEBUG
  // ライティング計算
  SetUseLighting(FALSE);
  _collisionEvent.Draw(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
  SetUseLighting(TRUE);
#endif
}

void ActorMainGame::DrawCollisionSearch(vector4 color)
{
#if _DEBUG
  // ライティング計算
  SetUseLighting(FALSE);
  _collisionSearch.Draw(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
  SetUseLighting(TRUE);
#endif
}

void ActorMainGame::DrawCollisionObject(vector4 color)
{
#if _DEBUG
  // ライティング計算
  SetUseLighting(FALSE);
  _collision.DrawObject(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
  SetUseLighting(TRUE);
#endif
}

void ActorMainGame::SeGunShotPlay()
{
  ChangeVolumeSoundMem(255 * 80 / 100, gGlobal._se["se_gunshot"]);
  if (!(CheckSoundMem(gGlobal._se["se_gunshot"])))
  {
    PlaySoundMem(gGlobal._se["se_gunshot"], DX_PLAYTYPE_BACK);
  }
};