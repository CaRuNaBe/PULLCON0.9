/*
** WinMain
*/

//
// include ��
//

#include "../appframe.h"



//
// WinMain(). �v���O�����N���֐�
//
int WINAPI WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{
	auto appBase = ApplicationBase::GetInstance();
	if(!appBase)
	{
		return 0;
	}

	if(!appBase->Initialize(hInstance))
	{
		return 0;
	}

	// 1�t���[�����[�v��g�� ----------------------------------------------------------
	while(ProcessMessage() == 0)		// �v���O�������I������܂Ń��[�v
	{
		appBase->Input();
		appBase->Update();
		appBase->Draw();
	}

	appBase->Terminate();

	return 0;
}