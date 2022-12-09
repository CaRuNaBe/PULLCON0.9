
#include "appframe.h"


class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:
	ModeGame(ApplicationBase& game,int layer);
	virtual ~ModeGame();
	virtual bool Initialize();
	virtual bool Update();
	virtual bool Draw();

protected:



}; 
