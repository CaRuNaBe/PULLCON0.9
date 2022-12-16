
#include "appframe.h"
#include "ActorBase.h"

ActorBase::ActorBase() 
	:base()
{
	Init();
}

ActorBase::~ActorBase() {

}

void ActorBase::Init() {
	base::Init();


}

bool ActorBase::Update(ApplicationBase& game) {
	base::Update(game);
	return true;
}

bool ActorBase::Draw(ApplicationBase& game) {
	base::Draw(game);
	return true;
}