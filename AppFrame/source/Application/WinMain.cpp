/*
** WinMain
*/

//
// include 部
//

#include "../appframe.h"



//
// WinMain(). プログラム起動関数
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

	// 1フレームループを組む ----------------------------------------------------------
	while(ProcessMessage() == 0)		// プログラムが終了するまでループ
	{
		appBase->Input();
		appBase->Update();
		appBase->Draw();
	}

	appBase->Terminate();

	return 0;
}
