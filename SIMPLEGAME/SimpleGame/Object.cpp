#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	
}


Object::~Object()
{
}

void Object::update() {
	float elapsedTime = 1.5;
	m_x = m_x + m_vX = elapedTime;
	m_y = m_y + m_vy = elapedTime;

	if (m_x > 250)
		m_vX = -m_vX;
	if(m_x < -250)
		m_vX = -m_vX;


}
