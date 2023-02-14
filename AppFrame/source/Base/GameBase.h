#pragma once
class ApplicationBase;
class GameBase
{
public:
	GameBase( ApplicationBase& game,int layer );
	virtual ~GameBase();

	virtual bool Update() = 0;
	virtual bool Draw() = 0;
	virtual bool DebugDraw() = 0;

	virtual bool IsDead()
	{
		return is_dead;
	}
	virtual void Dead()
	{
		is_dead = true;
	}

	virtual bool GetUpdateSkip()
	{
		return is_update_skip;
	}

	virtual void SetUpdateSkip( bool update_skip )
	{
		is_update_skip = update_skip;
	}

	virtual bool GetDrawSkip()
	{
		return is_draw_skip;
	}

	virtual void SetDrawSkip( bool draw_skip )
	{
		is_draw_skip = draw_skip;
	}

	virtual int GetLayer()
	{
		return layer;
	}

protected:
	ApplicationBase& _game;
	bool is_dead;
	bool is_update_skip;
	bool is_draw_skip;
	int layer;
};

