#include "AppFrame.h"
#include "ApplicationMain.h"
#include "mode/ModeSpeakScript.h"
#include "mode/ModeSpeakScript.h"
// 実体
ApplicationMain g_oApplicationMain;

bool ApplicationMain::Initialize( HINSTANCE hInstance )
{
	if ( !base::Initialize( hInstance ) )
	{
		return false;
	}
	font_hundle = CreateFontToHandle( "Kazesawa-Bold",font_size,-1,-1 );

	// モードの登録
	std::string command;
	while ( true )
	{
		std::string buf = "";
		auto cchar = const_cast<char*>(buf.c_str());
		ClearDrawScreen();
		DrawString( 0,0,"コマンドを入力してください、記入方法 ファイル名/jsonファイル名",GetColor( 255,255,255 ) );
		///** 上記で表示したオブジェクトidを記入 ///
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

