class Player
{
public:
	int x, y, fightCount;
	Player()
	{
		x = 20;
		y = 7;
		fightCount = 0;
	}
	~Player() {}

	void isKeyPressed()
	{
		if (fightCount == 0)
		{
			y = 5;
			fightCount = 1;
		}
	}

	void filghtCounter()
	{
		if (y == 5)
		{
			fightCount++;
			if (fightCount == 30)
			{
				y = 7;
				fightCount = 0;
			}
		}
	}
};