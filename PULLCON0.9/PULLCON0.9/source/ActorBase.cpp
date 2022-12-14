
#include "appframe.h"
#include "ActorBase.h"

ActorBase::ActorBase() 
	:base()
{

}

ActorBase::~ActorBase() {

}

void ActorBase::Init() {
	base::Init();


}

void ActorBase::Update(ApplicationBase& game) {
	base::Update(game);

}

void ActorBase::Draw(ApplicationBase& game) {
	base::Draw(game);

}