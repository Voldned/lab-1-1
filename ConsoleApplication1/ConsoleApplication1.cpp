
#include <iostream>
#include <conio.h>
#include <math.h>
#include <random>

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glaux.h"

using namespace std;
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"glu32.lib")
#pragma comment (lib, "glaux.lib")

#pragma comment(lib, "legacy_stdio_definitions.lib")

byte GetRandByte(byte start, byte end)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(1, 10);

	return dist(gen);
}

void DrawRedOrbit(float r1, float r2)
{
	byte slices = 50;
	byte x = 0;
	byte y = 0;

	float angle = 2.0f * 3.14 / slices;

	glBegin(GL_QUAD_STRIP);
	for (int i = -3; i <= slices + 1; i++)
	{
		float dx1 = r1 * cosf(angle * i);
		float dy1 = r1 * sinf(angle * i);
		float dx2 = r2 * cosf(angle * i);
		float dy2 = r2 * sinf(angle * i);

		glColor3f(GetRandByte(0, 10) / 10.0, 0, 0);
		glVertex2f(x + dx1, y + dy1);
		glColor3f(GetRandByte(0, 10) / 10.0, 0, 0);
		glVertex2f(x + dx2, y + dy2);
	}
	glEnd();

}

void DrawBlackCircle(float r1)
{
	byte slices = 60;
	byte x = 0;
	byte y = 0;

	float angle = 2.0f * 3.14 / slices;

	glColor3f(0, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (int i = 0; i <= slices + 1; i++)
	{
		float dx = r1 * cosf(angle * i);
		float dy = r1 * sinf(angle * i);
		glVertex2f(x + dx, y + dy);
	}
	glEnd();
}

void DrawDisc(float r1, float r2)
{
	byte slices = 50;

	for (float i = r1; i <= r2; i += r1 / slices)
		DrawRedOrbit(i, i + r1 / slices);
	
	byte x = 0;
	byte y = 0;

	float angle = 2.0f * 3.14 / slices;

	glColor3f(0, 0, 0);
	glBegin(GL_QUAD_STRIP);
	for (int i = -3; i <= slices + 1; i++)
	{
		float dx1 = r2 * cosf(angle * i);
		float dy1 = r2 * sinf(angle * i);
		float dx2 = (r2+3) * cosf(angle * i);
		float dy2 = (r2 + 3) * sinf(angle * i);

		glVertex2f(x + dx1, y + dy1);
		glVertex2f(x + dx2, y + dy2);
	}
	glEnd();

}

void DrawHorizon(float r1, float r2)
{
	DrawRedOrbit(r1, r1 + 1);
	DrawBlackCircle(r2);
}

void DrawStars()
{
	byte slices = 20;

	float angle = 2.0f * 3.14 / slices;

	for (byte i = 0; i <= 10; i += 1)
	{	
		/*glColor3f(1, 1, 1);
		glBegin(GL_TRIANGLE_FAN);
		byte x = GetRandByte(1, 50);
		byte y = GetRandByte(1, 50);
		for (byte j = 0; j <= 20; j += 1)
		{
			float dx1 = 0.1 * cosf(angle * j);
			float dy1 = 0.1 * sinf(angle * j);
			glVertex2f(x + dx1, y + dy1);
		}
		glEnd();*/

		float trc = GetRandByte(1, 1000) / 100.0;

		glPointSize(10);
		glBegin(GL_POINTS);
			glColor3f(trc, trc, trc);
			glVertex2d(15, 20);
			glColor3f(0.8 + trc, 0.8 + trc, 0.8 + trc);
			glVertex2d(28, -15);
			glColor3f(0.6 - trc, 0.6 - trc, 0.6 - trc);
			glVertex2d(20, 5);
			glColor3f(0.4 + trc, 0.4 + trc, 0.4 + trc);
			glVertex2d(-19, -20);
			glColor3f(0.2 - trc, 0.2 - trc, 0.2 - trc);
			glVertex2d(-22, 10);
			glColor3f(0.9 + trc, 0.9 + trc, 0.9 + trc);
			glVertex2d(17, -5);
			glColor3f(0.1 - trc, 0.1 - trc, 0.1 - trc);
			glVertex2d(-27, 20);
			glColor3f(0.7 + trc, 0.7 + trc, 0.7 + trc);
			glVertex2d(-17, -10);
			glColor3f(0.5 + trc, 0.5 + trc, 0.5 + trc);
			glVertex2d(30, -18);
			glColor3f(0.3 - trc, 0.3 - trc, 0.3 - trc);
			glVertex2d(-25, 12);
			glColor3f(0.8 + trc, 0.8 + trc, 0.8 + trc);
			glVertex2d(-30, -7);
			glColor3f(0.6 - trc, 0.6 - trc, 0.6 - trc);
			glVertex2d(18, 18);
			glColor3f(0.4 + trc, 0.4 + trc, 0.4 + trc);
			glVertex2d(-33, -16);
			glColor3f(0.2 - trc, 0.2 - trc, 0.2 - trc);
			glVertex2d(25, 8);
			glColor3f(0.9 + trc, 0.9 + trc, 0.9 + trc);
			glVertex2d(-35, -12);
			glColor3f(0.1 - trc, 0.1 - trc, 0.1 - trc);
			glVertex2d(23, 15);
			glColor3f(0.7 + trc, 0.7 + trc, 0.7 + trc);
			glVertex2d(-20, -5);

		glEnd();
	}
}



void CALLBACK resize(int width, int height)
{
	float anglez = 0, anglex = 0, rz = 50;
	float ex = 0, ey = 0, ez = rz;
	float cx = 0, cy = 0, cz = 0;
	int w;
	int h;
	w = width;
	h = height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)width / height, 1.0, 10000.0);
	ex = rz * sin(anglez);
	ez = rz * cos(anglez);

	gluLookAt(ex, ey, ez, cx, cy, cz, 0, 1, 0);
	// glFrustum ( -1 , 1 , -1 , 1 , 1.25 , 10.0 ); //Область видимости
	glMatrixMode(GL_MODELVIEW);

	glClearColor(0.0, 0.0, 0.1, 1.0); //цвет фона
	//glClearDepth(1.0); // Разрешить очистку буфера глубины
	glEnable(GL_DEPTH_TEST); //включить тест глубины
}

void CALLBACK display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glPopMatrix();
	//glRotated(1, 0, 0.85, 0.15);
	//glPushMatrix();
	DrawStars();
	glRotated(-80, 1, 0, 0);
	DrawDisc(10 + GetRandByte(0, 10) / 10.0, 20 + GetRandByte(0, 10) / 10.0);
	glLoadIdentity();
	DrawHorizon(7 + GetRandByte(0, 5) / 10.0, 9 + GetRandByte(0, 5) / 10.0);
	Sleep(100);

	auxSwapBuffers();
}

void RunOpenGL()
{
	auxInitPosition(0, 0, 2000, 1000);
	auxInitDisplayMode(AUX_RGB | AUX_DEPTH | AUX_DOUBLE);
	auxInitWindow(L"Glaux Template");
	auxIdleFunc(display);
	auxReshapeFunc(resize);
	auxMainLoop(display);
	
	glEnable(GL_BLEND);//разрешаем смешивание при наложении
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//устанавливаем наиболее подходящие параметры смешивания
}

void main()
{
	RunOpenGL();
}