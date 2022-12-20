
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

bool ActorBase::Update(ApplicationBase& game,ModeBase& mode ) {
	base::Update(game,mode );
	return true;
}

bool ActorBase::Draw(ApplicationBase& game,ModeBase& mode ) {
	base::Draw(game,mode );
	return true;
}