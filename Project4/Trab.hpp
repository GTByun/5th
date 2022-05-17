#include <random>
#include "Object.hpp"

using namespace std;
class Trab : public Object
{
private:
	const double speed = 11.0f;
public:
	double length;
	bool isOn;

	Trab()
	{
		Hide();
	}
	~Trab() {}
	void Initialize()
	{
		x = 40;
		random_device rd;
		mt19937 gen(rd());
		//uniform_int_distribution<int> dis(1, 2);
		uniform_real_distribution<double> dis3(1.0f, 2.0f);
		length = dis3(gen);
		uniform_int_distribution<int> dis2(5, 7);
		y = dis2(gen);
		isOn = true;
	}
	void Hide()
	{
		x = 0;
		y = 0;
		length = 0;
		isOn = false;
	}
	
	void Move(double deltaTime)
	{
		x -= deltaTime * speed;
	}

	bool Collider(Object* obj)
	{
		double x = obj->x, y = obj->y;
		bool xCondition = abs(x - this->x) < 1;
		double ySub = y - this->y;
		bool yCondition = ySub > -length && ySub < 1;
		return xCondition && yCondition;
	}
};