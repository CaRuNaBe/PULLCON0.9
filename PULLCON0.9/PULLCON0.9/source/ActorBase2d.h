#pragma once
#include "appframe.h"
using namespace math;
class ActorBase2d:public ObjectBase
{
	using base = ObjectBase;
public:
	enum class Type
	{  // ��ʂ̗񋓌^
		KBASE,			// 0 �A�N�^�[
		KPLAYER,		// 1 �v���C���[
		KTITLELOGO,	// 2 �^�C�g�����S
		KGAMESTARTLOGO,			// 3 �Q�[���X�^�[�g���S
		KCREDITLOGO,	// 4 �N���W�b�g���S
		KENDLOGO,		// 5 �Q�[���I�����S
	};
	virtual Type GetType() = 0;

	ActorBase2d();
	virtual ~ActorBase2d();

	virtual void	Init();
	virtual bool	Update(ApplicationBase& game);
	virtual void	UpdateCollision();
	virtual bool	Draw(ApplicationBase& game);
	virtual void	DrawCollision();

	virtual AABB& GetCollision()
	{
		return _collision;
	}
	virtual bool	IsDead()
	{
		return _dead;
	}
	virtual void	Dead()
	{
		_dead = true;
	}
	virtual Vector2& GetPosition()
	{
		return _pos;
	}
	virtual void	SetPosition(Vector2 pos)
	{
		_pos = pos;
	}
	virtual Vector2& GetSize()
	{
		return _size;
	}
	virtual void	SetSize(Vector2 size)
	{
		_size = size;
	}
	virtual bool	IsHitObject(ActorBase2d& object);	// �w��̃I�u�W�F�N�g�Ɠ������Ă��邩�H
protected:
	Vector2	_pos;		// ���W
	Vector2 _size;		// �傫��
	float	_spd;		// �ړ����x
	AABB	_collision;	// �����蔻��p��`
	Vector2	_colPos,_colSize;	// �����蔻��ʒu�T�C�Y(_pos����̍���)

	int		_cnt;		// ����J�E���^
};

/*
// ObjectBase�N���X
class ObjectBase
{
public:
	ObjectBase(Game& game,ModeBase& mode);
	virtual ~ObjectBase();

	enum class Type
	{  // ��ʂ̗񋓌^
		kBase,			// 0 �A�N�^�[
		kPlayer,		// 1 �v���C���[
		kBackground,	// 2 �w�i
		kEnemy,			// 3 �G�l�~�[
		kPlayerBullet,	// 4 �v���C���[�̒e
		kEffect,		// 5 �G�t�F�N�g
	};
	virtual Type	GetType() = 0;

	virtual void	Init();
	virtual void	Update();
	virtual void	UpdateCollision();
	virtual void	Render();
	virtual void	DrawCollision();
	virtual AABB& GetCollision()
	{
		return _collision;
	}
	virtual void	Damage();
	virtual bool	IsDead()
	{
		return _dead;
	}
	virtual void	Dead()
	{
		_dead = true;
	}
	virtual Vector2& GetPosition()
	{
		return _pos;
	}
	virtual void	SetPosition(Vector2 pos)
	{
		_pos = pos;
	}
	virtual Vector2& GetSize()
	{
		return _size;
	}
	virtual void	SetSize(Vector2 size)
	{
		_size = size;
	}
	virtual bool	IsHitObject(ObjectBase& object);	// �w��̃I�u�W�F�N�g�Ɠ������Ă��邩�H

protected:
	Game& _game;
	ModeBase& _mode;
	bool	_dead;

	Vector2	_pos;		// ���W
	Vector2 _size;		// �傫��
	float	_spd;		// �ړ����x
	AABB	_collision;	// �����蔻��p��`
	Vector2	_colPos,_colSize;	// �����蔻��ʒu�T�C�Y(_pos����̍���)
	int		_hit_noCnt;	// �J�E���^��1�ȏ�̏ꍇ�͓����蔻�肵�Ȃ�

	int		_cnt;		// ����J�E���^
};
*/