#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ApplicationGlobal.h"
#include "mode/ModeTitle.h"
#include "mode/ModeSpeakScript.h"
#include "ModeTest.h"
// ����
ApplicationMain g_oApplicationMain;

bool ApplicationMain::Initialize( HINSTANCE hInstance )
{
	if ( !base::Initialize( hInstance ) )
	{
		return false;
	}
	font_hundle = CreateFontToHandle( "Kazesawa-Bold",font_size,-1,-1 );
	gGlobal.Init();
#if 0
	auto title = std::make_shared<ModeTitle>( *this,1 );
	base::GetInstance()->GetModeServer()->Add( title );
#endif // 0
#if 0
	auto test = std::make_shared<ModeTest>( *this,1 );
	base::GetInstance()->GetModeServer()->Add( test );
#endif
#if 1
	// ���[�h�̓o�^
	std::string command;
	while ( true )
	{
		std::string buf = "";
		auto cchar = const_cast<char*>(buf.c_str());
		ClearDrawScreen();
		DrawString( 0,0,"�R�}���h����͂��Ă��������A�L�����@ �t�@�C����/json�t�@�C����",GetColor( 255,255,255 ) );
		///** ��L�ŕ\�������I�u�W�F�N�gid���L�� ///
		if ( KeyInputSingleCharString( 0,20,50,cchar,TRUE ) == 1 )
		{
			command = cchar;
			if ( command.empty() )
			{
				continue;
			}
			break;
		}
	}
	auto game = std::make_unique<ModeSpeakScript>( *this,1,command );
	base::GetInstance()->GetModeServer()->Add( std::move( game ) );
#endif
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

