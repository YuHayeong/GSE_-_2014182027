#include "stdafx.h"
#include "Object.h"


Object::Object(float x, float y)
{
	m_x = x;
	m_y = y;
	m_vX = 1;
	m_vY = 0;

	m_size = 10;
	m_color[0] = 1;
	m_color[1] = 1;
	m_color[2] = 1;
	m_color[3] = 1;
}


Object::~Object()
{
	
}

void Object::Update()
{
	float elapsedTime = 0.1;
	m_x = m_x + m_vX * elapsedTime;
	m_y= m_y + m_vY * elapsedTime;

	if (m_x > 250)
		m_vX = -m_vX;

	if (m_x < -250)
		m_vX = -m_vX;
}