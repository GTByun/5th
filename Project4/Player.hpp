class Player
{
private:
	const double gravity = -75.0f;
public:
	double x, y, jumpPower;
	Player()
	{
		Reset();
	}
	~Player() {}

	void Reset()
	{
		x = 20;
		y = 7;
		jumpPower = 0;
	}

	void isSpacePressed()
	{
		if (y >= 7)
		{
			jumpPower = -19.0f;
		}
	}

	void isDownPressed()
	{
		jumpPower = 25.0f;
	}

	void filghtCounter(double deltaTime)
	{
		double carY = y;
		carY += jumpPower * deltaTime;
		jumpPower -= gravity * deltaTime;
		y = carY <= 7 ? carY : 7;
	}
};