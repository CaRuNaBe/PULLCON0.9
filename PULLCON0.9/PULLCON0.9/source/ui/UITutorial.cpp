#include "UITutorial.h"
namespace {
	constexpr int TUTORIAI_BUTTON_A  = 55;
	constexpr int TUTORIAI_BUTTON_B  = 55;
	constexpr int TUTORIAI_BUTTON_X  = 100;
	constexpr int TUTORIAI_BUTTON_R2 = 60;

}
UITutorial::UITutorial(ApplicationBase& game, int layer, ModeMainGame& _base)
	:UIBase(game, layer, _base) {
	handle_tutorial_A  = ResourceServer::LoadGraph("res/2D_image/tutorial/UI_Tutorial_A.png");
	handle_tutorial_B  = ResourceServer::LoadGraph("res/2D_image/tutorial/UI_Tutorial_B.png");
	handle_tutorial_X  = ResourceServer::LoadGraph("res/2D_image/tutorial/UI_Tutorial_X.png");
	handle_tutorial_R2 = ResourceServer::LoadGraph("res/2D_image/tutorial/UI_Tutorial_R2.png");
	Initialize();
};

UITutorial::~UITutorial() {
};

bool UITutorial::Initialize() {
	UIBase::Initialize();
	return true;
};

bool UITutorial::Update() {
	UIBase::Update();
	return true;
};

bool UITutorial::Draw() {
	UIBase::Draw();
	int y =150, size = 38;
		DrawRotaGraph(TUTORIAI_BUTTON_A , y, 1.0f, 0, handle_tutorial_A , TRUE); y += size;
		DrawRotaGraph(TUTORIAI_BUTTON_B , y, 1.0f, 0, handle_tutorial_B , TRUE); y += size;
		DrawRotaGraph(TUTORIAI_BUTTON_X , y, 1.0f, 0, handle_tutorial_X , TRUE); y += size;
		DrawRotaGraph(TUTORIAI_BUTTON_R2, y, 1.0f, 0, handle_tutorial_R2, TRUE);
	
	return true;
};
