#pragma once
#include "Object.h"

#define MAX_OBJECT_COUNT 1000
class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();



	int AddActorObject();
	void UpdateAllActorObjects();
	//void DeleteActorObject(int index);
	Object* GetActorObject(int index);
	//int GetMaxObjectCount();

private:
	Object * m_Objects[MAX_OBJECT_COUNT];
};

