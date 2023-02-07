#pragma once
/*****************************************************************//**
 * \file   ActorBase2d.h
 * \brief  2D�\���p�I�u�W�F�N�g�x�[�X
 *
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#include "../Math/math.h"
#include "ObjectBase.h"
using namespace math;
class ActorBase2d:public ObjectBase
{
	using base = ObjectBase;
public:
	enum class Type
	{
		// ��ʂ̗񋓌^
		/** �^�C�g����� */
		KBASE,			     // 0 �A�N�^�[
		KPLAYER,		     // 1 �v���C���[
		KTITLELOGO,	     // 2 �^�C�g�����S
		KGAMESTARTLOGO,	 // 3 �Q�[���X�^�[�g���S
		KGAMESTARTGUID,  // 4 �Q�[���X�^�[�g�K�C�h
		KCREDITLOGO,	   // 5 �N���W�b�g���S
		KCREDITGUID,     // 6 �N���W�b�g�K�C�h
		KENDLOGO,		     // 7 �Q�[���I�����S
		KENDGUID,        // 8 �Q�[���I���K�C�h
		/** �|�[�Y��� */
		KPAUSELOGO,      // 9 �|�[�Y��ʂ̕\�����S
		KDESCRIPTIONLOGO,// 10 �|�[�Y��ʂ̑���������S
		KRESTARTLOGO,    // 11 �|�[�Y��ʂ̍ăX�^�[�g���S
		KRETURNTITLELOGO,    // 12 �|�[�Y��ʂ̃^�C�g���ɖ߂郍�S
		/** ���U���g��� */
		/** �Q�[���I�[�o�[��� */
	};
	virtual Type GetType() = 0;

	ActorBase2d( ApplicationBase& game,ModeBase& mode );
	virtual ~ActorBase2d();

	virtual void	Init();/*������*/
	virtual bool	Update();//
	virtual void	UpdateCollision();
	virtual bool	Draw();
	virtual void	DrawCollision();

	virtual AABB& GetCollision()
	{
		return _collision;
	}

	virtual Vector2& GetPosition()
	{
		return _pos;
	}
	virtual void	SetPosition( Vector2 pos )
	{
		_pos = pos;
	}
	virtual Vector2& GetSize()
	{
		return _size;
	}
	virtual void	SetSize( Vector2 size )
	{
		_size = size;
	}
	virtual bool	IsHitObject( ActorBase2d& object );	// �w��̃I�u�W�F�N�g�Ɠ������Ă��邩�H
protected:
	Vector2	_pos;		// ���W
	Vector2 _size;		// �傫��
	float	_spd;		// �ړ����x
	AABB	_collision;	// �����蔻��p��`
	Vector2	_colPos,_colSize;	// �����蔻��ʒu�T�C�Y(_pos����̍���)
	EasingMode _easing = nullptr;
	int		_cnt;		// ����J�E���^
};
