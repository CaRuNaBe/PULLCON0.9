
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "ModePause.h"
#include "ModeGame.h"
#include "ModeTitle.h"
// 実体
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	// モードの登録
	auto game = std::make_shared<ModePause>(*this,1);
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

