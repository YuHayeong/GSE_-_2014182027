#include "stdafx.h"
#include "Object.h"
#include "SceneMgr.h"
#include <math.h>


Object::Object(float x, float y, int type)
{
	m_x = x;
	m_y = y;

	m_type = type;

	m_lastBullet = 0;
	m_lastArrow = 0;

	m_parentID = -1;

	if (type == OBJECT_BUILDING)
	{
		m_color[0] = 1;
		m_color[1] = 0;
		m_color[2] = 0;
		m_color[3] = 1;

		m_vX = 0;
		m_vY = 0;

		m_size = 50;
		m_life = 500;

		m_lifeTime = 100000;	

		
	}
	if (type == OBJECT_BUILDING2)
	{
		m_color[0] = 0;
		m_color[1] = 0;
		m_color[2] = 1;
		m_color[3] = 1;

		m_vX = 0;
		m_vY = 0;

		m_size = 50;
		m_life = 500;

		m_lifeTime = 100000;


	}
	else if (type == OBJECT_CHARACTER)
	{
		m_color[0] = 0;
		m_color[1] = 0;
		m_color[2] = 1;
		m_color[3] = 1; 
		
		m_vX = 300 *(((float)std::rand() / (float)RAND_MAX) - 0.5);
		m_vY = 300 *(((float)std::rand() / (float)RAND_MAX) - 0.5);
		
		m_size = 10;
		m_life = 10;

		m_lifeTime = 100000;
	}
	else if (type == OBJECT_BULLET)
	{
		m_color[0] = 1;
		m_color[1] = 0;
		m_color[2] = 0;
		m_color[3] = 1;

		m_vX = 600 *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_vY = 600 *(((float)std::rand() / (float)RAND_MAX) - 0.5f);

		m_size = 2;
		m_life = 20;

		m_lifeTime = 100000;
	}
	else if (type == OBJECT_BULLET2)
	{
		m_color[0] = 0;
		m_color[1] = 0;
		m_color[2] = 1;
		m_color[3] = 1;

		m_vX = 600 * (((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_vY = 600 * (((float)std::rand() / (float)RAND_MAX) - 0.5f);

		m_size = 2;
		m_life = 20;

		m_lifeTime = 100000;
	}
	else if (type == OBJECT_ARROW)
	{
		m_color[0] = 0;
		m_color[1] = 1;
		m_color[2] = 0;
		m_color[3] = 1;

		m_vX = 100 *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_vY = 200 *(((float)std::rand() / (float)RAND_MAX) - 0.5f);

		m_size = 2;
		m_life = 10;

		m_lifeTime = 100000.f;
	}
	else
	{
		std::cout << "Wrong Object Type " << type << " \n";
	}
}

Object::~Object()
{
	
}

void Object::Update(float elapsedTime)
{
	float elapsedTimeInSecond = elapsedTime / 1000.f;

	m_lastBullet += elapsedTimeInSecond;
	m_lastArrow += elapsedTimeInSecond;

	m_x = m_x + m_vX * elapsedTimeInSecond;
	m_y= m_y + m_vY * elapsedTimeInSecond;

	if (m_x > 250)
	{
		if (m_type == OBJECT_BULLET)
		{
			m_life = 0.f;
		}

		m_vX = -m_vX;
	}

	if (m_x < -250)
	{
		if (m_type == OBJECT_BULLET)
		{
			m_life = 0.f;
		}

		m_vX = -m_vX;
	}

	if (m_y > 500)
	{
		if (m_type == OBJECT_BULLET)
		{
			m_life = 0;
		}

		m_vY = -m_vY;
	}

	if (m_y < -500)
	{
		if (m_type == OBJECT_BULLET)
		{
			m_life = 0;
		}

		m_vY = -m_vY;
	}

	if (m_life > 0)
	{
		if (m_type != OBJECT_BUILDING)
		{
			//m_life -= 0.5f;
		}
	}

	if (m_lifeTime > 0.f)
	{
//		m_lifeTime -= elapsedTimeInSecond;
	}
}

float Object::GetLife()
{
	return m_life;
}

float Object::GetLifeTime()
{
	return m_lifeTime;
}

int Object::GetType()
{
	return m_type;
}

void Object::SetDamage(float amount)
{
	m_life -= amount;
}
