#pragma once
#include <cstdlib>
#include <iostream>

#include "Renderer.h"
#include "Object.h"

#define MAX_OBJECT_COUNT 50000

class SceneMgr
{
public:
	SceneMgr(int width, int height);
	~SceneMgr();

	int AddActorObject(float x, float y);
	void DeleteActorObject(int index);
	void UpdateAllActorObjects();
	Object* GetActorObject(int index);
	int GetMaxObjectCount();
	void DrawAllObjects();

private:
	bool BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);
	void DoCollisionTest();
	Object *m_actorObjects[MAX_OBJECT_COUNT];
	Object *m_bulletObjects[MAX_OBJECT_COUNT];

	Renderer *m_renderer;

	int m_windowWidth;
	int m_windowHeight;
};

