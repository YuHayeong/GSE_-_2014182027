#include "stdafx.h"
#include "SceneMgr.h"

SceneMgr::SceneMgr(int width, int height)
{
	// Initialize Renderer
	m_renderer = new Renderer(width, height);

	Sound *m_sound;
	m_sound = new Sound();
	int soundBG = m_sound->CreateSound("./Dependencies/SoundSamples/MF-W-90.XM");
	m_sound->PlaySound(soundBG, true, 0.2f);
	
	if (!m_renderer->IsInitialized())
	{
		std::cout << "SceneMgr::Renderer could not be initialized.. \n";
	}

	m_windowWidth = width;
	m_windowHeight = height;
	m_texCharacter = m_renderer->CreatePngTexture("./Textures/simpsons.png");
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		m_actorObjects[i] = NULL;
		m_bulletObjects[i] = NULL;
	}
}

int g_temp = 0;

void SceneMgr::DrawAllObjects()
{
	

	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_actorObjects[i] != NULL)
		{
			m_renderer->DrawSolidRect(
				m_actorObjects[i]->m_x,
				m_actorObjects[i]->m_y,
				0,
				m_actorObjects[i]->m_size,
				m_actorObjects[i]->m_color[0],
				m_actorObjects[i]->m_color[1],
				m_actorObjects[i]->m_color[2],
				m_actorObjects[i]->m_color[3],
				0
			);
		}
	}
}

SceneMgr::~SceneMgr()
{
}

int SceneMgr::AddActorObject(float x, float y, int type)
{
	//Find empty slot
	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_actorObjects[i] == NULL)
		{
			m_actorObjects[i] = new Object(x, y, type);
			return i;
		}
	}

	//slots are full
	std::cout << "slots are full \n";
	return -1;
}

void SceneMgr::DeleteActorObject(int index)
{
	if (m_actorObjects[index] != NULL)
	{
		delete m_actorObjects[index];
		m_actorObjects[index] = NULL;
	}
}

void SceneMgr::UpdateAllActorObjects(float elapsedTime)
{
	DoCollisionTest();

	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		if (m_actorObjects[i] != NULL)
		{
			if (m_actorObjects[i]->GetLife() < 0.0001f || m_actorObjects[i]->GetLifeTime() < 0.0001f)
			{
				delete m_actorObjects[i];
				m_actorObjects[i] = NULL;
			}
			else
			{
				m_actorObjects[i]->Update(elapsedTime);
				if (m_actorObjects[i]->GetType() == OBJECT_BUILDING)
				{
					//fire bullet
					if (m_actorObjects[i]->m_lastBullet > 0.5f)
					{
						int bulletID = AddActorObject(
							m_actorObjects[i]->m_x,
							m_actorObjects[i]->m_y,
							OBJECT_BULLET);
						m_actorObjects[i]->m_lastBullet = 0.f;
						if (bulletID >= 0)
						{
							m_actorObjects[bulletID]->m_parentID = i;
						}
					}
				}
			}
		}
		if (m_bulletObjects[i] != NULL)
		{
			m_bulletObjects[i]->Update(elapsedTime);
		}
	}
}

Object* SceneMgr::GetActorObject(int index)
{
	return m_actorObjects[index];
}

int SceneMgr::GetMaxObjectCount()
{
	return MAX_OBJECT_COUNT;
}

void SceneMgr::DoCollisionTest()
{
	int collisionCount = 0;

	for (int i = 0; i < MAX_OBJECT_COUNT; i++)
	{
		collisionCount = 0;
		if (m_actorObjects[i] != NULL)
		{
			for (int j = i+1; j < MAX_OBJECT_COUNT; j++)
			{
				if (m_actorObjects[j] != NULL && m_actorObjects[i] != NULL)
				{
					float minX, minY;
					float maxX, maxY;

					float minX1, minY1;
					float maxX1, maxY1;

					minX = m_actorObjects[i]->m_x - m_actorObjects[i]->m_size / 2.f;
					minY = m_actorObjects[i]->m_y - m_actorObjects[i]->m_size / 2.f;
					maxX = m_actorObjects[i]->m_x + m_actorObjects[i]->m_size / 2.f;
					maxY = m_actorObjects[i]->m_y + m_actorObjects[i]->m_size / 2.f;
					minX1 = m_actorObjects[j]->m_x - m_actorObjects[j]->m_size / 2.f;
					minY1 = m_actorObjects[j]->m_y - m_actorObjects[j]->m_size / 2.f;
					maxX1 = m_actorObjects[j]->m_x + m_actorObjects[j]->m_size / 2.f;
					maxY1 = m_actorObjects[j]->m_y + m_actorObjects[j]->m_size / 2.f;

					if (BoxBoxCollisionTest(minX, minY, maxX, maxY, minX1, minY1, maxX1, maxY1))
					{
						if (
							(m_actorObjects[i]->GetType() == OBJECT_BUILDING)
							&&
							(m_actorObjects[j]->GetType() == OBJECT_CHARACTER)
							)
						{
							m_actorObjects[i]->SetDamage(m_actorObjects[j]->GetLife());
							m_actorObjects[j]->m_life = 0.f;
							collisionCount++;
						}
						else if (
							(m_actorObjects[j]->GetType() == OBJECT_BUILDING)
							&&
							(m_actorObjects[i]->GetType() == OBJECT_CHARACTER)
							)
						{
							m_actorObjects[j]->SetDamage(m_actorObjects[i]->GetLife());
							m_actorObjects[i]->m_life = 0.f;
							collisionCount++;
						}else if (
							(m_actorObjects[i]->GetType() == OBJECT_CHARACTER)
							&&
							(m_actorObjects[j]->GetType() == OBJECT_BULLET)
							)
						{
							m_actorObjects[i]->SetDamage(m_actorObjects[j]->GetLife());
							m_actorObjects[j]->m_life = 0.f;
						}
						else if (
							(m_actorObjects[j]->GetType() == OBJECT_CHARACTER)
							&&
							(m_actorObjects[i]->GetType() == OBJECT_BULLET)
							)
						{
							m_actorObjects[j]->SetDamage(m_actorObjects[i]->GetLife());
							m_actorObjects[i]->m_life = 0.f;
						}
					}
				}
			}

			if ( collisionCount > 0 )
			{
				if (m_actorObjects[i] != NULL && m_actorObjects[i]->GetType() == OBJECT_BUILDING)
				{
					m_actorObjects[i]->m_color[0] = 1;
					m_actorObjects[i]->m_color[1] = 0;
					m_actorObjects[i]->m_color[2] = 0;
					m_actorObjects[i]->m_color[3] = 1;
				}
			}
			else
			{
				if (m_actorObjects[i] != NULL && m_actorObjects[i]->GetType() == OBJECT_BUILDING)
				{
					m_actorObjects[i]->m_color[0] = 1;
					m_actorObjects[i]->m_color[1] = 1;
					m_actorObjects[i]->m_color[2] = 0;
					m_actorObjects[i]->m_color[3] = 1;
				}
			}
		}
	}
}

bool SceneMgr::BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1)
{
	if (minX > maxX1)
		return false;
	if (maxX < minX1)
		return false;

	if (minY > maxY1)
		return false;
	if (maxY < minY1)
		return false;

	return true;
}
