
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "mode/ModeTest.h"
// 実体
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }
	font_hundle = CreateFontToHandle( "Kazesawa-Bold",font_size,-1,-1 );
	// モードの登録
	auto game = std::make_shared<ModeTest>(*this,1);
	base::GetInstance()->GetModeServer()->Add(game);

	return true;
}

bool ApplicationMain::Terminate() {
	base::Terminate();
	return true;
}


bool ApplicationMain::Input() {
	base::Input();
	return true;
}

bool ApplicationMain::Update() {
	base::Update();
	return true;
}

bool ApplicationMain::Draw() {
	base::Draw();
	return true;
}

