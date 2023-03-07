#pragma once
#include "appframe.h"
#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
// カメラ
class Camera {
public:
	vector4	_vPos;					// 位置
	vector4	_vPosEvent;			// 引っこ抜きカメラ位置
	vector4	_vTarget;				// 注視点
	vector4	_vMemory;				// ベクトル保存用
	float	_clipNear, _clipFar;	// クリップ
};

class Player : public ActorBase3D {
	typedef ActorBase3D base;
public:
	Player( ApplicationBase& game,ModeMainGame& mode );
	virtual ~Player();
	virtual Type GetType() { return Type::kPlayer; }
	// プレイヤーの状態
	enum class State {
		NUM, //初期状態
		PLAY,//プレイアブル状態
		EVENT//イベント状態
	};

	virtual void Init();
	virtual bool Update();
	virtual bool Draw();

	void CameraUpdate();    // カメラ更新
	void EventCamera();    // カメラ
	void AddBullet(vector4 pos);
	State GetPlayerState() {
		return _statePlayer;
	}
	int GetPush() {
		return _push;
	}
protected:
	// カメラ
	Camera	_cam;

	State  _statePlayer;

	vector4 _vMoveDir;
	int    _push;             // ボタン連打回数
	bool   _isLerp;           // 線形補間するか
	bool   _isHit;            // 当たったか
	bool   _isHitObject;      // オブジクトと当たったか
	float  _fSpeedIint;       // プレイヤーの速度の初期値
	float  _fTime;            // 線形補間の経過時間
	float  _fRotateAirscrew;  // プロペラの回転
	float  _fAxialX;
	float  _fAxialZ;

	int    _handleBody;
	int    _handleAirscrew;
	int    _handleMagnet;
	int    _handleBackAirscrew;
	int    _handlefont;
	int    _handleStage;
	int    _se;
	int    _seBullet;

};
