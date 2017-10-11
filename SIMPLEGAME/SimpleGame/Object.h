#pragma once
class Object
{
	char name[50];
	int hp;
	int mp;
	int power;
	int speed;
	int m_x, m_y;
	int m_vX, m_vY;

public:
	Object();
	Object(float x, float y) {
		m_x = x;
		m_y = y;
	};
	
	~Object();

	void update();


};

