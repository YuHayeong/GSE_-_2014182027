/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"

#include "Object.h"

Renderer *g_Renderer = NULL;
Object *g_Object = NULL;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	// Renderer Test
	g_Renderer->DrawSolidRect(
		g_Object->m_x, 
		g_Object->m_y,
		0, 
		g_Object->m_size,
		g_Object->m_color[0],
		g_Object->m_color[1],
		g_Object->m_color[2],
		g_Object->m_color[3]
	);

	g_Object->Update();
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
	g_Object->Update();
}

//button
//GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON,GLUT_RIGHT_BUTTON
//state
//GLUT_UP, GLUT_DOWN

void MouseInput(int button, int state, int x, int y)
{
	//if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN) {
	//	g_LButtonDoin = true;
	//}
	//if (button == GLUT_LEFT_BUTTON&&state == GLUT_UP) {
	//	//clicked
	//	//범위체크
	//	
	//
	//}



	RenderScene();
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);

	g_Object = new Object(0, 0);

	glutMainLoop();

	delete g_Renderer;
	delete g_Object;

    return 0;
}

