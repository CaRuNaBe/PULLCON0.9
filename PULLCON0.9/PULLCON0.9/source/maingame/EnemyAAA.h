#pragma once
#include "appframe.h"
#include "ActorBase3D.h"
#include "../mode/ModeMainGame.h"
#include <string>
#include <sstream>
#include <array>
class EnemyAAA: public ActorBase3D
{
	typedef ActorBase3D base;
public:
	EnemyAAA( ApplicationBase& game,ModeMainGame& mode,int min_id,int max_id,int pile_num,float scale,vector4 _vPosi );
	virtual ~EnemyAAA();
	virtual Type GetType()
	{
		return Type::kEnemyAAA;
	}
// �΋�C�̏��
	enum class State
	{
		NUM,//�n���̑΋�C
		PLAY,//�v���C�A�u�����
		EVENT,//�C�x���g���
		WEAPON//���퉻
	};

	virtual void Init( int pile_num,vector4 _vPosi );
	virtual bool Update();
	virtual bool Draw();

	virtual void Damage();
	void AddBullet( const int& theta_split_num,const int& phi_split_num,const int& theta_degree_lower,const int& theta_degree_upper,const int& phi_degree_lower,const int& phi_degree_upper );
	void AddPieces( int pile_num );
	void GetSearch();
	void AddPieces( int min_id,int max_id,int pile_num,float scale );

	void SetAxialX( float _x_rad )
	{
		_fAxialX = _x_rad;
	}
	void SetAxialY( float _y_rad )
	{
		_fAxialY = _y_rad;
	}
	void SetType( int _aim_player )
	{
		_iType = _aim_player;
	}
protected:
	State   _stateAAA;

	int    _iType;  // �^�C�v 0,�ǔ��� 1,�Œ莮
	int    _iPossession;  // �΋�C�p�[�c�̏��L��
	float  _fAxialY;  // Y����](�x���@)	
	float  _fAxialX;  // X����](�x���@)
	bool   _get;  // �����Ă��邩

	int    _handle_body;
	int    _handle_turret;
	int AAA_ID;
	std::vector<int>bullet_state;
	
};
