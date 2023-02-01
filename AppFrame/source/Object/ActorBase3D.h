#pragma once

#include "../Math/math.h"
#include "ObjectBase.h"
using namespace math;
class ActorBase3D : public ObjectBase {
	typedef ObjectBase base;
public:
	ActorBase3D();
	virtual ~ActorBase3D();

	enum class Type {  // ��ʂ̗񋓌^
		kBase,          // 0 �A�N�^�[
		kPlayer,        // 1 �v���C���[
		kBullet,        // 2 �e��
		kEnemyAAA,      // 3 �΋�C
		kClearObject,   // 5 �ŏI�ڕW
		kSkySphere,     // 6 �X�J�C�X�t�B�A
		kGameStage,     // 7 �Q�[���X�e�[�W
		kSupplyEria,    // 8 �⋋�n�_
		kEffect,        // n �G�t�F�N�g
	};
	virtual Type GetType() = 0;

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual void	UpdateCollision();
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);
	virtual void	DrawCollision(vector4 color);
	virtual void	DrawCollisionEvent(vector4 color);
	virtual void	DrawCollisionSearch(vector4 color);

	virtual bool	IsHitObject(ActorBase3D& object);	// �w��̃I�u�W�F�N�g�Ɠ������Ă��邩
	virtual bool	IsHitEvent(ActorBase3D& object);	// �C�x���g�X�t�B�A�Ɠ������Ă��邩
	virtual bool	IsSearch(ActorBase3D& object);	  // �T�[�`�X�t�B�A�Ɠ������Ă��邩

	virtual void Damage(ModeBase& mode) {}

	virtual Sphere& GetCollision() { return _collision; }
	virtual Sphere& GetCollisionEvent() { return _collisionEvent; }
	virtual Sphere& GetCollisionSearch() { return _collisionSearch; }

	// ���W�̐ݒ�
	void SetPosition(const vector4& pos) { _vPos = pos; }
	void SetPosition(float x, float y, float z) { _vPos.x = x; _vPos.y = y; _vPos.z = z; }
	virtual vector4& GetPosition() { return _vPos; }
	// �����x�N�g���̐ݒ�
	void SetDir(const vector4& dir) { _vDir = dir; }
	void SetDir(float x, float y, float z) { _vDir.x = x; _vDir.y = y; _vDir.z = z; }

public:
	vector4 _vPos;   // �ʒu
	vector4 _vEvent;   // �C�x���g�ʒu
	vector4 _vRelation;   // �ʒu�֌W
	vector4 _vTarget;   // �ڕW�ʒu
	vector4 _vDir;   // ����

	Sphere  _collision;   // ������
	Sphere  _collisionEvent;   // �C�x���g����
	Sphere  _collisionSearch;   // ���G����

	int   _iFuel;    // �R��
	int   _iLife;    // ���C�t
	int   _iDamage;  // �^����_���[�W
	int   _iPieces;  // ��
	float _fSpeed;   // ���x
	float _fScale;   // �傫��
	float _fRotatX;  // X����]
	float _fRotatY;  // Y����]
	bool  _coll;   // �R���W������������邩
	bool  _overlap;   // ���肪�d�Ȃ�����
	bool  _event;   // �C�x���g����Əd�Ȃ�����
	bool  _pull;    // �C�x���g
	bool  _finish;   // �C�x���g����
	bool  _fire;    // ���C

	int _cnt;  // ����J�E���g
	int _CT;   // �N�[���^�C��
	int _ST;   // ��������
};