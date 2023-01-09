#pragma once

#include "../Math/math.h"
#include "ObjectBase.h"
using namespace math;
class ActorBase : public ObjectBase {
	typedef ObjectBase base;
public:
	ActorBase();
	virtual ~ActorBase();

	enum Type {  // ��ʂ̗񋓌^
		kBase,     // 0 �A�N�^�[
		kPlayer,   // 1 �v���C���[
		kBullet,   // 2 �e��
		kEnemyAAA, // 3 �΋�C
	};
	virtual Type GetType() = 0;

	virtual void Init();
	virtual bool Update(ApplicationBase& game, ModeBase& mode);
	virtual bool Draw(ApplicationBase& game, ModeBase& mode);

	virtual void Damage(ModeBase& mode) {}

	// ���W�̐ݒ�
	void SetPosition(const vector4& pos) { _vPos = pos; }
	void SetPosition(float x, float y, float z) { _vPos.x = x; _vPos.y = y; _vPos.z = z; }
	// �����x�N�g���̐ݒ�
	void SetDir(const vector4& dir) { _vDir = dir; }
	void SetDir(float x, float y, float z) { _vDir.x = x; _vDir.y = y; _vDir.z = z; }
public:
	vector4 _vPos;
	vector4 _vDir;

	float _speed;

	int _cnt;  // ����J�E���g
	int _ST;   // ��������
};