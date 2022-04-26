#include <random>

using namespace std;
class Trab
{
public:
	int x, y, length, moveCount;
	bool isOn;
	Trab()
	{
		Hide();
	}
	~Trab() {}
	void Initialize()
	{
		x = 40;
		moveCount = 0;
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> dis(1, 2);
		length = dis(gen);
		uniform_int_distribution<int> dis2(5, 7);
		y = dis2(gen);
		isOn = true;
	}
	void Hide()
	{
		x = 0;
		y = 0;
		moveCount = 0;
		length = 0;
		isOn = false;;
	}
	
	void MoveConter()
	{
		moveCount++;
		if (moveCount == 3)
		{
			x--;
			moveCount = 0;
		}
	}
};