#include "stdafx.h"
#include "SceneMgr.h"

#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"
#include "Object.h"

SceneMgr::SceneMgr()
{
	
	for (int i = 0;i < MAX_OBJECT_COUNT; i++)
	{
		m_Objects[i] = NULL;
	}
}


SceneMgr::~SceneMgr()
{
}

int SceneMgr::AddActorObject()
{
	for (int i=0; i<MAX_OBJECT_COUNT;i++ )
		if (m_Objects[i] == NULL)
		{
			float x = 250*(std::rand() / (float)RAND_MAX - 0.5f);
			float y = 250 * (std::rand() / (float)RAND_MAX - 0.5f);
			m_Objects[i] = new Object(x, y);
			return i;
		}
	//
	std::cout << "slots are full\n";
	return -1;
}

void SceneMgr::UpdateAllActorObjects() {


}

Object*SceneMgr::GetActorObject(int index) {
	return 0;
}
