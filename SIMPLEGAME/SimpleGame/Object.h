#pragma once
class Object
{
public:
	Object(float x, float y);
	~Object();

	void Update();

	float m_x;
	float m_y;
	float m_vX;
	float m_vY;

	float m_size;
	float m_color[4];
};

