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
	};
	virtual Type GetType() = 0;

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual void	UpdateCollision();
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);
	virtual void	DrawCollision();
	virtual bool	IsHitObject(ActorBase3D& object);	// �w��̃I�u�W�F�N�g�Ɠ������Ă��邩

	virtual void Damage(ModeBase& mode) {}

	virtual Sphere& GetCollision() { return _collision; }

	// ���W�̐ݒ�
	void SetPosition(const vector4& pos) { _vPos = pos; }
	void SetPosition(float x, float y, float z) { _vPos.x = x; _vPos.y = y; _vPos.z = z; }
	// �����x�N�g���̐ݒ�
	void SetDir(const vector4& dir) { _vDir = dir; }
	void SetDir(float x, float y, float z) { _vDir.x = x; _vDir.y = y; _vDir.z = z; }
public:
	vector4 _vPos;
	vector4 _vDir;

	Sphere  _collision;

	float _speed;

	int _cnt;  // ����J�E���g
	int _CT;   // �N�[���^�C��
	int _ST;   // ��������
};