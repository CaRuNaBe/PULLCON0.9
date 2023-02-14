
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "mode/ModeMainGame.h"
// 実体
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize( HINSTANCE hInstance )
{
	if ( !base::Initialize( hInstance ) )
	{
		return false;
	}
	font_hundle = CreateFontToHandle( "Kazesawa-Bold",font_size,-1,-1 );
	// モードの登録
	/*
	while ( true )
	{
		std::string buf = "";
		auto cchar = const_cast<char*>(buf.c_str());
		ClearDrawScreen();
		DrawString( posix,posiy,inputname.c_str(),GetColor( 255,255,255 ) );
		///** 上記で表示したオブジェクトidを記入 ///
		if ( KeyInputSingleCharString( posix,posiy + 500,50,cchar,TRUE ) == 1 )
		{
			std::string ecommandbuf = cchar;


		}
		else
		{
		}
	}
 */
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

