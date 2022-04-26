class Player
{
public:
	int x, y, flightCount;
	Player()
	{
		Reset();
	}
	~Player() {}

	void Reset()
	{
		x = 20;
		y = 7;
		flightCount = 0;
	}

	void isSpacePressed()
	{
		if (flightCount == 0)
		{
			y = 5;
			flightCount = 1;
		}
	}

	void isDownPressed()
	{
		if (flightCount != 0 && flightCount < 25)
		{
			flightCount = 25;
		}
	}

	void filghtCounter()
	{
		if (flightCount != 0)
		{
			flightCount++;
			if (abs(flightCount - 15) > 10)
				y = 6;
			else
				y = 5;
			if (flightCount == 30)
			{
				y = 7;
				flightCount = 0;
			}
		}
	}
};