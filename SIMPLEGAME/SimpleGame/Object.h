#pragma once
#include <cstdlib>

class Object
{
public:
	Object(float x, float y, int type);
	~Object();

	float GetLife();
	float GetLifeTime();
	int GetType();
	void SetDamage(float amount);
	
	void Update(float elapsedTime);

	float m_x;
	float m_y;
	float m_vX;
	float m_vY;

	float m_size;
	float m_color[4];

	float m_life;
	float m_lifeTime;

	int m_type;

	float m_lastBullet;
	float m_lastArrow;

	int m_parentID;
};

