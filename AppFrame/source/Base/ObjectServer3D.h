/*****************************************************************//**
 * \file   ObjectServer.h
 * \brief  �Q�[���ɓo�ꂷ����̂��ׂĂ��Ǘ�����N���X
 *
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
#pragma once
#include <memory>
#include <vector>
#include "GameBase.h"
template<class T>class ObjectServer3D
{
public:
	using ObjectPtr = std::shared_ptr<T>;//�I�u�W�F�N�g�N���X�|�C���^ObjectBase���p�������N���X�̂ݑΉ�
	using TypeObjects = std::vector <ObjectPtr >;// �I�u�W�F�N�g���X�g���`
	/** �R���X�g���N�^ */
	ObjectServer3D():_updating( false )
	{}
	/** �f�X�g���N�^ */
	~ObjectServer3D()
	{
		Clear();
	}
	/** _v3DObjects�擾 */
	TypeObjects& Get3DObjects()
	{
		return _v3DObjects;
	}
	/** _vBillboardObjects�擾 */
	TypeObjects& GetBillboardObjects()
	{
		return _vBillboardObjects;
	}
	/** �S�N���A */
	void Clear()
	{
		Clear3DObjects();
		ClearBillboardObjects();
	}
	/** _v3DObjects������ */
	void Clear3DObjects()
	{
		_v3DObjects.clear();
	}
	/** _vBillboardObjects������ */
	void ClearBillboardObjects()
	{
		_vBillboardObjects.clear();
	}
	/** _updating��true�̎��͒ǉ��\�񂷂� */
	void Add3Dobject( ObjectPtr object )
	{
		if ( _updating )
		{
			_vPending3DObjects.push_back( object );
		}
		else
		{
			_v3DObjects.push_back( object );
		}
	}
	/** _updating��true�̎��͒ǉ��\�񂷂� */
	void AddBillboardObject( ObjectPtr object )
	{
		if ( _updating )
		{
			_vPendingBillboardObjects.push_back( object );
		}
		else
		{
			_vBillboardObjects.push_back( object );
		}
	}
	/** �폜�\�񂷂� */
	void Del( T& object )
	{
		object.Dead();
	}
	/** �X�V���� ���t���[���Ă΂�� */
	bool Update()
	{
		_updating = true;//�����J�n
		for ( auto&& object : _v3DObjects )
		{
			if ( object->GetUpdateSkip() )
			{
				continue;//�X�L�b�v����
			}
			object->Update();
		}
		for ( auto&& object : _vBillboardObjects )
		{
			if ( object->GetUpdateSkip() )
			{
				continue;//�X�L�b�v����
			}
			object->Update();
		}
		_updating = false;//�����I��
		AddPendingObjects();//_v3DObjects�ɒǉ������̃t���[�����瓮����
		DeleteObjects();// �폜�\�񂳂ꂽ�I�u�W�F�N�g���폜����
		return true;
	}
	/** �`�揈�� ���t���[���Ă΂�� */
	bool Draw()
	{
		for ( auto itr = std::rbegin( _v3DObjects ); itr != std::rend( _v3DObjects ); ++itr )
		{
			if ( (*itr)->GetDrawSkip() )
			{
				continue;//�`��X�L�b�v
			}
			(*itr)->Draw();
		}
		for ( auto itr = std::rbegin( _vBillboardObjects ); itr != std::rend( _vBillboardObjects ); ++itr )
		{
			if ( (*itr)->GetDrawSkip() )
			{
				continue;//�`��X�L�b�v
			}
			(*itr)->Draw();
		}
		return true;
	}
protected:
	/** 3D�I�u�W�F�N�g������R���e�i */
	TypeObjects _v3DObjects;
	/** 3D�I�u�W�F�N�g����Œǉ����邽�߂̃R���e�i */
	TypeObjects _vPending3DObjects;
	/** �r���{�[�h�ō��ꂽ���̂�����R���e�i */
	TypeObjects _vBillboardObjects;
	/** �r���{�[�h�I�u�W�F�N�g����Œǉ����邽�߂̃R���e�i */
	TypeObjects _vPendingBillboardObjects;
	/** _v3DObjects���񂵂Ă���Ƃ���true�ɂ��� */
	bool _updating;
	/** Del�֐��ŃI�u�W�F�N�g������ł����ꍇ_v3DObjects����erase �܂���_vBillboardObjects����erase*/
	void DeleteObjects()
	{
		// _v3DObjects���C�e���[�^�ŉ�( erase���C�e���[�^��v�����Ă��邽�� )
		for ( auto ite = _v3DObjects.begin(); ite != _v3DObjects.end(); )
		{
			if ( (*ite)->IsDead() )
			{
				ite = _v3DObjects.erase( ite );// �����object���̂��̂��폜�����
			}
			else
			{
				++ite;//���ɐi�߂�
			}
		}
		// _vBillboardObjects���C�e���[�^�ŉ�( erase���C�e���[�^��v�����Ă��邽�� )
		for ( auto ite = _vBillboardObjects.begin(); ite != _vBillboardObjects.end(); )
		{
			if ( (*ite)->IsDead() )
			{
				ite = _vBillboardObjects.erase( ite );// �����object���̂��̂��폜�����
			}
			else
			{
				++ite;//���ɐi�߂�
			}
		}
	}
	/** _vPending3DObjects �̒��ɂ�����̂� _v3DObjects �ɒǉ� �܂���_vPendingBillboardObjects�̒��ɂ�����̂�_vBillboardObjects�ɒǉ�*/
	void AddPendingObjects()
	{
		// _vPending3DObjects -> _v3DObjects �ɒǉ�
		_v3DObjects.insert( _v3DObjects.end(),make_move_iterator( _vPending3DObjects.begin() ),make_move_iterator( _vPending3DObjects.end() ) );
		// _vPending3DObjects ���N���A
		_vPending3DObjects.clear();
		// _vPendingBillboardObjects -> _vBillboardObjects �ɒǉ�
		_vBillboardObjects.insert( _vBillboardObjects.end(),make_move_iterator( _vPendingBillboardObjects.begin() ),make_move_iterator( _vPendingBillboardObjects.end() ) );
		// _vPendingBillboardObjects ���N���A
		_vPendingBillboardObjects.clear();
	}
};

