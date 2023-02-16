
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModeTest.h"
#include "mode/ModeMainGame.h"
// ����
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize( HINSTANCE hInstance )
{
	if ( !base::Initialize( hInstance ) )
	{
		return false;
	}
	font_hundle = CreateFontToHandle( "Kazesawa-Bold",font_size,-1,-1 );

	auto game = std::make_unique<ModeMainGame>( *this,1 );
	base::GetInstance()->GetModeServer()->Add( std::move( game ) );

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

