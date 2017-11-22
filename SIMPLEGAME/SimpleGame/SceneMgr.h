#pragma once
#include <cstdlib>
#include <iostream>

#include "Renderer.h"
#include "Object.h"

#define MAX_OBJECT_COUNT 300

#define OBJECT_CHARACTER 0
#define OBJECT_BUILDING 11
#define OBJECT_BUILDING2 12
#define OBJECT_BULLET 21
#define OBJECT_BULLET2 22
#define OBJECT_ARROW 3

class SceneMgr
{
public:
	SceneMgr(int width, int height);
	~SceneMgr();

	int AddActorObject(float x, float y, int type);
	void DeleteActorObject(int index);
	void UpdateAllActorObjects(float elapsedTime);
	Object* GetActorObject(int index);
	int GetMaxObjectCount();
	void DrawAllObjects();

private:
	bool BoxBoxCollisionTest(float minX, float minY, float maxX, float maxY, float minX1, float minY1, float maxX1, float maxY1);
	void DoCollisionTest();
	Object *m_actorObjects[MAX_OBJECT_COUNT];
	Object *m_bulletObjects[MAX_OBJECT_COUNT];

	Renderer *m_renderer;
	int m_texCharacter;
	int m_windowWidth;
	int m_windowHeight;
};

