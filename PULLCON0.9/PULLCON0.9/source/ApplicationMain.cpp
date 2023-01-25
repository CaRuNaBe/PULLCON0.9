
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "mode/ModePause.h"
#include "mode/ModeGame.h"
#include "mode/ModeMainGame.h"
#include "mode/ModeTitle.h"
// é¿ëÃ
ApplicationMain				g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!base::Initialize(hInstance)) { return false; }

	// ÉÇÅ[ÉhÇÃìoò^
	auto game = std::make_shared<ModeMainGame>(*this,1);
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

