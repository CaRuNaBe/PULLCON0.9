#pragma once
#include "appframe.h"

using namespace math;
class ModeMainGame;
class ActorMainGame : public GameBase
{
public:
  ActorMainGame(ApplicationBase& game, int layer, ModeMainGame& mode);
  virtual ~ActorMainGame();

  enum class Type
  {  // 種別の列挙型
    kBase,          // 0 アクター
    kPlayer,        // 1 プレイヤー
    kBullet,        // 2 弾丸
    kEnemyAAA,      // 3 対空砲
    kEnemySkyhunter,// 4 スカイハンター
    kEnemyGunShip,   // 5 最終目標
    kSkySphere,     // 6 スカイスフィア
    kGameStage,     // 7 ゲームステージ
    kAreaSupply,    // 8 補給地点
    kStageObject,   // 9 ステージオブジェクト
    kAreaEnemySpawn,// 10 敵スポーンエリア
    kAreaCommunication,//11会話スクリプト起動エリア
    kAreaNoEntry,   // 12 侵入不能エリア
    kEffect,        // n エフェクト
  };
  virtual Type GetType() = 0;

  virtual void Initialize();
  virtual bool Update();
  virtual void UpdateCollision();
  virtual bool Draw();
  virtual void DrawCollision(Vector4 color);
  virtual void DrawCollisionEvent(Vector4 color);
  virtual void DrawCollisionSearch(Vector4 color);
  virtual void DrawCollisionObject(Vector4 color);
  virtual bool DebugDraw();
  virtual bool IsHitObject(ActorMainGame& object);// 指定のオブジェクトと当たっているか
  virtual bool IsHitEvent(ActorMainGame& object);// イベントスフィアと当たっているか
  virtual bool IsSearch(ActorMainGame& object);// サーチスフィアと当たっているか

  virtual void Damage()
  {
  }

  virtual Sphere& GetCollision()
  {
    return _collision;
  }
  virtual Sphere& GetCollisionEvent()
  {
    return _collisionEvent;
  }
  virtual Sphere& GetCollisionSearch()
  {
    return _collisionSearch;
  }

  virtual void SeGunShotPlay();
  // 座標の設定
  void SetPosition(const Vector4& pos)
  {
    _vPos = pos;
  }
  void SetPosition(float x, float y, float z)
  {
    _vPos.x = x; _vPos.y = y; _vPos.z = z;
  }
  virtual Vector4& GetPosition()
  {
    return _vPos;
  }
  // 向きベクトルの設定
  void SetDir(const Vector4& dir)
  {
    _vDir = dir;
  }
  void SetDir(float x, float y, float z)
  {
    _vDir.x = x; _vDir.y = y; _vDir.z = z;
  }

  void SetScale(float _scale)
  {
    _fScale = _scale;
  };
  void SetCollision(const Vector4& pos, float _radius)
  {
    _collision._vCenter = pos;
    _fRadius = _radius;
  };
  void SetCollisionRadius(float radius)
  {
    _fRadius = radius;
  };
  void SetSpeed(float _speed)
  {
    _fSpeed = _speed;
  };
  int GetFuel()
  {
    return _iFuel;
  }
  int GetLife()
  {
    return _iLife;
  }
  Vector4 GetTarget()
  {
    return _vTarget;
  }
  bool GetEvent()
  {
    return _event;
  }
public:
  ModeMainGame& _mode;
  Vector4 _vPos;       // 位置
  Vector4 _vEvent;     // イベント位置
  Vector4 _vRelation;  // 位置関係
  Vector4 _vTarget;    // 目標位置
  Vector4 _vDir;       // 向き
  Vector4 _vVelocity;  // 速度ベクトル

  Sphere  _collision;        // 球判定
  Sphere  _collisionEvent;   // イベント判定
  Sphere  _collisionSearch;  // 索敵判定

  int   _iFuel;      // 燃料
  int   _iLife;      // ライフ
  int   _iDamage;    // 与えるダメージ
  int   _iPieces;    // 個数
  int   _iPart;      // 各パーツの番号
  int   _iType;      // 使用する弾の種類
  float _fSpeed;     // 速度
  float _fScale;     // 大きさ
  float _fRotatX;    // X軸回転
  float _fRotatY;    // Y軸回転
  bool  _coll;       // コリジョン判定をするか
  bool  _overlap;    // 判定が重なったか
  bool  _event;      // イベント判定と重なったか
  bool  _pull;       // 引っこ抜き
  bool  _finish;     // イベント完了
  bool  _fire;       // 発砲
  bool  _synchronize;// 動きを同期させる
  bool  _takeIn;     // オブジェクトとぶつかったか

  int _cnt;  // 動作カウント
  int _CT;   // クールタイム
  int _ST;   // 生存時間

  float _fRadius;
};