#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "mode/ModeMainGame.h"
#include "mode/ModeSpeakScript.h"
// ����
ApplicationMain g_oApplicationMain;

bool ApplicationMain::Initialize( HINSTANCE hInstance )
{
	if ( !base::Initialize( hInstance ) )
	{
		return false;
	}
	font_hundle = CreateFontToHandle( "Kazesawa-Bold",font_size,-1,-1 );
	// �A�v���P�[�V�����O���[�o���̏�����
	gGlobal.Init();
	auto game = std::make_shared<ModeSpeakScript>( *this,1,"gameover/gameover" );
	base::GetInstance()->GetModeServer()->Add( game );

	return true;
}

bool ApplicationMain::Terminate()
{
	base::Terminate();
	return true;
}


bool ApplicationMain::Input()
{
	base::Input();
	return true;
}

bool ApplicationMain::Update()
{
	base::Update();
	return true;
}

bool ApplicationMain::Draw()
{
	base::Draw();
	return true;
}

