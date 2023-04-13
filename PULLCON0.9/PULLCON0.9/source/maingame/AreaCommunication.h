
#pragma once
#include "appframe.h"
#include "ActorMainGame.h"
#include "../mode/ModeMainGame.h"
#include <string>
class AreaCommunication :public ActorMainGame
{
public:
  AreaCommunication(ApplicationBase& game, int layer,ModeMainGame& mode, const std::string& storyname);
  virtual ~AreaCommunication();
  virtual Type GetType()
  {
    return Type::kAreaCommunication;
  }
  virtual void Initialize();
  virtual bool Update();
  virtual bool Draw();

protected:
  std::string storyname;
};


