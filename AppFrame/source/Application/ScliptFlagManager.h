#pragma once
/*****************************************************************//**
 * \file   ScliptFlagManager.h
 * \brief �X�N���v�g����t���O�N���X
 *
 * \author ���������Y
 * \date   December 2022
 *********************************************************************/
class ScliptFlagManager
{
public:
	ScliptFlagManager();
	~ScliptFlagManager();
	bool GetisEndsclipt()
	{
		return isEndsclipt;
	}
	bool GetisLoadend()
	{
		return isLoadend;
	}
	bool GetisBlackbackground()
	{
		return isBlackbackground;
	}
	void SetisEndsclipt(const bool Endsclipt)
	{
		isEndsclipt = Endsclipt;
	}
	void SetisLoadend(const bool Loadend)
	{
		isLoadend = Loadend;
	}
	void SetisBlackbackground(const bool Blackbackground)
	{
		isBlackbackground = Blackbackground;
	}
private:
	bool isEndsclipt;//�X�N���v�g���I��点��Ƃ�true
	bool isLoadend;//�X�N���v�g���J�����Ɠ����Ƀ��[�f�B���O��ʂ��J�������Ɏg�p���[�f�B���O���I�������true
	bool isBlackbackground;//�X�N���v�g���J���Ă��鎞���̉�ʂ�\���Ǘ��t���Otrue�̎�����ʂ͉f��Ȃ�
};

