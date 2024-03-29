#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
// カメラ
class Camera
{
public:
	Vector4	_vPos;					// 位置
	Vector4	_vPosEvent;			// 引っこ抜きカメラ位置
	Vector4	_vTarget;				// 注視点
	Vector4	_vMemory;				// ベクトル保存用
	float	_clipNear, _clipFar;	// クリップ
};

class Player : public ActorMainGame
{
public:
	Player(ApplicationBase& game, int layer, ModeMainGame& mode);
	virtual ~Player();
	virtual Type GetType()
	{
		return Type::kPlayer;
	}
	// プレイヤーの状態
	enum class State
	{
		NUM, //初期状態
		PLAY,//プレイアブル状態
		EVENT//イベント状態
	};

	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();

	void CameraUpdate();    // カメラ更新
	void EventCamera();    // カメラ
	void AddBullet(Vector4 pos);
	State GetPlayerState()
	{
		return _statePlayer;
	}
	int GetPush()
	{
		return _push;
	}
protected:
	// カメラ
	Camera	_cam;

	State  _statePlayer;

	Vector4 _vMoveDir;
	int    _push;                 // ボタン連打回数
	bool   _isLerp;               // 線形補間するか
	bool   _isHit;                // 当たったか
	bool   _isHitObject;          // オブジクトと当たったか
	float  _fSpeedIint;           // プレイヤーの速度の初期値
	float  _fTime;                // 線形補間の経過時間
	float  _fRotateAirscrew;      // プロペラの回転
	float  _fRotateBackAirscrew;  // バックプロペラの回転
	float  _fAxialX;              // ヘリコプターのX軸回転
	float  _fAxialZ;							// ヘリコプターのZ軸回転

	int    _handleBody;
	int    _handleAirscrew;
	int    _handleMagnet;
	int    _handleBackAirscrew;
	int    _handleStage;


};
