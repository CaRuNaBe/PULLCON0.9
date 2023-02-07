
#include "ApplicationBase.h"

ApplicationBase* ApplicationBase::_lpInstance = NULL;


ApplicationBase::ApplicationBase()
{
	_lpInstance = this;
	font_hundle = 0;
	font_size = 29;
}

ApplicationBase::~ApplicationBase()
{
}

bool ApplicationBase::Initialize( HINSTANCE hInstance )
{
#if _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	// DXライブラリの初期化
	if ( AppWindowed() )
	{
		ChangeWindowMode( true );							// ウィンドウモードに指定する
	}
	SetGraphMode( DispSizeW(),DispSizeH(),32 );


	if ( DxLib_Init() == -1 )
	{	// エラーが起きたら直ちに終了
		return false;
	}
	SetDrawScreen( DX_SCREEN_BACK );		// 描画先画面を裏画面にセット

	// Ｚバッファを有効にする
	SetUseZBuffer3D( TRUE );

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D( TRUE );

	// モードサーバの初期化
	_serverMode = std::make_shared<ModeServer>( *this );

	font_hundle = 0;
	font_size = 29;
	return true;
}

bool ApplicationBase::Terminate()
{
	InitFontToHandle();
	// DXライブラリ開放
	DxLib_End();

	return true;
}


bool ApplicationBase::Input()
{
	_input.Update();
	return true;
}

bool ApplicationBase::Update()
{
	_serverMode->UpdateInit();
	_serverMode->Update();
	_serverMode->UpdateFinish();
	return true;
}


bool ApplicationBase::Draw()
{
	_serverMode->DrawInit();
	_serverMode->Draw();
	_serverMode->DrawFinish();
	return true;
}
