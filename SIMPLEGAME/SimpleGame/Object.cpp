#include "stdafx.h"
#include "Object.h"
#include <math.h>


Object::Object(float x, float y)
{
	m_x = x;
	m_y = y;
	m_vX = 4.f*(((float)std::rand() / (float)RAND_MAX) - 0.5f);
	m_vY = 4.f*(((float)std::rand() / (float)RAND_MAX) - 0.5f);

	m_size = 10;
	m_color[0] = 1;
	m_color[1] = 1;
	m_color[2] = 1;
	m_color[3] = 1;

	m_life = 100;
}


Object::~Object()
{
	
}

void Object::Update()
{
	float elapsedTime = 1.5f;
	m_x = m_x + m_vX * elapsedTime;
	m_y= m_y + m_vY * elapsedTime;

	//m_size = 30.f * (sin(m_x)+1)/2;
	//m_color[0] = cos(m_x);
	//m_color[1] = cos(m_x);
	//m_color[3] = cos(3.141592f*0.5*((10.f-m_life) / 10.f));

	if (m_x > 250)
	{
		m_vX = -m_vX;
	}

	if (m_x < -250)
	{
		m_vX = -m_vX;
	}

	if (m_y > 250)
	{
		m_vY = -m_vY;
	}

	if (m_y < -250)
	{
		m_vY = -m_vY;
	}

	if (m_life > 0.f)
	{
		//m_life -= 0.5f;
	}
}

float Object::GetLife()
{
	return m_life;
}