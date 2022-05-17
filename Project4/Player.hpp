#include "Object.hpp"

class Player : public Object
{
private:
	const double gravity = -75.0f;
	double jumpPower;
public:
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
			jumpPower = -21.0f;
		}
	}

	void isDownPressed()
	{
		jumpPower = 25.0f;
	}

	void Flight(double deltaTime)
	{
		double carY = y;
		carY += jumpPower * deltaTime;
		jumpPower -= gravity * deltaTime;
		y = carY <= 7 ? carY : 7;
	}
};