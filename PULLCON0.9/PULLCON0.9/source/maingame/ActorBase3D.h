#pragma once
#include "appframe.h"

#include "../ObjectBase.h"
using namespace math;
class ModeMainGame;
class ActorBase3D : public ObjectBase {
	typedef ObjectBase base;
public:
	ActorBase3D(ApplicationBase& game, ModeMainGame& mode);
	virtual ~ActorBase3D();

	enum class Type {  // ��ʂ̗񋓌^
		kBase,          // 0 �A�N�^�[
		kPlayer,        // 1 �v���C���[
		kBullet,        // 2 �e��
		kEnemyAAA,      // 3 �΋�C
		kEnemySkyhunter,// 4 �X�J�C�n���^�[
		kClearObject,   // 5 �ŏI�ڕW
		kSkySphere,     // 6 �X�J�C�X�t�B�A
		kGameStage,     // 7 �Q�[���X�e�[�W
		kAreaSupply,    // 8 �⋋�n�_
		kStageObject,   // 9 �X�e�[�W�I�u�W�F�N�g
		kAreaEnemySpawn,// 10 �G�X�|�[���G���A
		kAreaCommunication,//11��b�X�N���v�g�N���G���A
		kAreaNoEntry,   // 12 �N���s�\�G���A
		kEffect,        // n �G�t�F�N�g
	};
	virtual Type GetType() = 0;

	virtual void Init();
	virtual bool Update();
	virtual void	UpdateCollision();
	virtual bool Draw();
	virtual void	DrawCollision(vector4 color);
	virtual void	DrawCollisionEvent(vector4 color);
	virtual void	DrawCollisionSearch(vector4 color);
	virtual void	DrawCollisionObject(vector4 color);

	virtual bool	IsHitObject(ActorBase3D& object);	// �w��̃I�u�W�F�N�g�Ɠ������Ă��邩
	virtual bool	IsHitEvent(ActorBase3D& object);	// �C�x���g�X�t�B�A�Ɠ������Ă��邩
	virtual bool	IsSearch(ActorBase3D& object);	  // �T�[�`�X�t�B�A�Ɠ������Ă��邩

	virtual void Damage() {
	}

	virtual Sphere& GetCollision() {
		return _collision;
	}
	virtual Sphere& GetCollisionEvent() {
		return _collisionEvent;
	}
	virtual Sphere& GetCollisionSearch() {
		return _collisionSearch;
	}

	virtual void SeGunShotPlay();
	// ���W�̐ݒ�
	void SetPosition(const vector4& pos) {
		_vPos = pos;
	}
	void SetPosition(float x, float y, float z) {
		_vPos.x = x; _vPos.y = y; _vPos.z = z;
	}
	virtual vector4& GetPosition() {
		return _vPos;
	}
	// �����x�N�g���̐ݒ�
	void SetDir(const vector4& dir) {
		_vDir = dir;
	}
	void SetDir(float x, float y, float z) {
		_vDir.x = x; _vDir.y = y; _vDir.z = z;
	}

	void SetScale(float _scale) {
		_fScale = _scale;
	};
	void SetCollision(const vector4& pos, float _radius) {
		_collision._vCenter = pos;
		_fRadius = _radius;
	};
	void SetCollisionRadius(float radius) {
		_fRadius = radius;
	};
	void SetSpeed(float _speed) {
		_fSpeed = _speed;
	};
	int GetFuel() {
		return _iFuel;
	}
	int GetLife() {
		return _iLife;
	}
	vector4 GetTarget() {
		return _vTarget;
	}
	bool GetEvent() {
		return _event;
	}
public:
	ModeMainGame& _mode;
	vector4 _vPos;       // �ʒu
	vector4 _vEvent;     // �C�x���g�ʒu
	vector4 _vRelation;  // �ʒu�֌W
	vector4 _vTarget;    // �ڕW�ʒu
	vector4 _vDir;       // ����
	vector4 _vVelocity;  // ���x�x�N�g��

	Sphere  _collision;        // ������
	Sphere  _collisionEvent;   // �C�x���g����
	Sphere  _collisionSearch;  // ���G����

	int   _iFuel;      // �R��
	int   _iLife;      // ���C�t
	int   _iDamage;    // �^����_���[�W
	int   _iPieces;    // ��
	int   _iPart;      // �e�p�[�c�̔ԍ�
	int   _iType;      // �g�p����e�̎��
	float _fSpeed;     // ���x
	float _fScale;     // �傫��
	float _fRotatX;    // X����]
	float _fRotatY;    // Y����]
	bool  _coll;       // �R���W������������邩
	bool  _overlap;    // ���肪�d�Ȃ�����
	bool  _event;      // �C�x���g����Əd�Ȃ�����
	bool  _pull;       // ����������
	bool  _finish;     // �C�x���g����
	bool  _fire;       // ���C
	bool  _synchronize;// �����𓯊�������
	bool  _takeIn;     // �I�u�W�F�N�g�ƂԂ�������

	int _cnt;  // ����J�E���g
	int _CT;   // �N�[���^�C��
	int _ST;   // ��������

	float _fRadius;
};