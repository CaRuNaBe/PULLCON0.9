#pragma once
class ApplicationBase;
class GameBase
{
public:
	GameBase( ApplicationBase& game,int layer );
	virtual ~GameBase();

	virtual bool Initialize() = 0;
	virtual bool Update() = 0;
	virtual bool Draw() = 0;
	virtual bool DebugDraw() = 0;

	bool IsDead()
	{
		return dead;
	}
	void Dead()
	{
		dead = true;
	}

	bool GetUpdateSkip()
	{
		return isUpdateSkip;
	}

	void SetUpdateSkip( bool UpdateSkip )
	{
		isUpdateSkip = UpdateSkip;
	}

	bool GetDrawSkip()
	{
		return isDrawSkip;
	}

	void SetDrawSkip( bool DrawSkip )
	{
		isDrawSkip = DrawSkip;
	}

	int GetLayer()
	{
		return layer;
	}

protected:
	ApplicationBase& game;
	bool dead;
	bool isUpdateSkip;
	bool isDrawSkip;
	int layer;
};

