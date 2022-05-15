// клавиши влево/вправо вращают по Y
// клавиши вверх/вниз вращают по X
// F1 - возвращает в начальное положение
// F2 - возращает в положение из input.txt файла, проверка на корректность (выход в случае ошибки)
// F3 - сохраняет положение кубика в output.txt файл
// F4 - проверяет кубик на корректность
// F5 - решение
// F9 - отдаление
// F10 - приближение 
// если нажали клавишу от 0 до 5 - поворот кубика
// правая кнопка мыши - рандомизация (второй клик, чтобы остановить) 

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <GLUT/glut.h>

#include "GraphixCube.h"

#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <unistd.h>

#define CUBE_SIZE 18
#define TIMER 0.01


//цвета для куба
unsigned int c[9] = {0xFAEBD7, 0xFFFF00, 0x0000FF, 0x5CCD32, 0xFF0000, 	0xFFa812};
 
// координаты источника света, ни на что не влияют
GLfloat lightPos[] = {0, 0, 0, 0}; 
// проекции угла поворота на оси
int xRotation = 25, yRotation = 40, zRotation = 40;
// отдаление
double distance = -40.0;

Cube cube;
// флаг, крутящегося кубика
int timerOn = 0;
 
void display()
{
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glTranslatef(0, 0, distance);
	glRotatef(xRotation, 1, 0, 0);
	glRotatef(yRotation, 0, 1, 0);
	glTranslatef(CUBE_SIZE / -2.0, CUBE_SIZE / -2.0, CUBE_SIZE / -2.0);
	cube.draw();
	glPopMatrix();
	glutSwapBuffers();
}
 
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat fAspect = (GLfloat)w/(GLfloat)h;
    gluPerspective(60, fAspect, 1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	srand(time(0));
 
	// освещение, без него страшно :D
	float mat_specular[] = {0.3, 0.3, 0.3, 0};
	float diffuseLight[] = {0.2, 0.2, 0.2, 1};
	float ambientLight[] = {0.9, 0.9, 0.9, 1.0};
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
 
	// инициализируем куб
	cube.clear(CUBE_SIZE, c);
}
 
void specialKeys(int key, int, int)
{
	if (key == GLUT_KEY_DOWN)
	{
		xRotation += 3;
		if (xRotation >= 360)
			xRotation -= 360;
		glutPostRedisplay();
	}
 
	if (key == GLUT_KEY_UP)
	{
		xRotation -= 3;
		if (xRotation < 0)
			xRotation += 360;
		glutPostRedisplay();
	}
 
	if (key == GLUT_KEY_RIGHT)
	{
		yRotation += 3;
		if (yRotation >= 360)
			yRotation -= 360;
		glutPostRedisplay();
	}
 
	if (key == GLUT_KEY_LEFT)
	{
		yRotation -= 3;
		if (yRotation < 0)
			yRotation += 360;
		glutPostRedisplay();
	}
 
	if (key == GLUT_KEY_F10)
	{
		distance += 5;
		glutPostRedisplay();
	}
 
	if (key == GLUT_KEY_F9)
	{
		distance -= 5;
		glutPostRedisplay();
	}
 
	if (key == GLUT_KEY_F1)
	{
		cube.clear(CUBE_SIZE, c);
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_F2)
	{
		cube.fillIn(CUBE_SIZE);
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_F3)
	{
		cube.fillOut(CUBE_SIZE);
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_F4){
		cube.check(CUBE_SIZE);
	}

	if (key == GLUT_KEY_F5){

		for (int i = cube.solution.size() - 1; i >= 0; --i){
			if (cube.solution[i].second){
				cube.rot90(cube.solution[i].first, -1);
			}
			else{
				cube.rot90(cube.solution[i].first, 1);
			}
			sleep(1);
			display();
		}
		cube.solution.clear();
		glutPostRedisplay();
		
	}
}
 
void keys(unsigned char key, int, int)
{
	if (cube.current == -1 && key >= '0' && key < '6')
	{
		cube.Rotate(key - '0', 3);
		display();
	}
}
 
void mouse(int key, int state, int, int)
{
	if (key == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		timerOn = 1 - timerOn;
	}
}
 
void timer(int)
{
	glutTimerFunc(TIMER, timer, 0);

	if (timerOn)
	{
		keys(rand() % 6 + '0', 0, 0);
		cube.Rotate(cube.current, -3);
	}
	else
	{
		if (cube.current != -1)
			cube.Rotate(cube.current, 3);
	}

	display();
}
 
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 700);
	glutInitWindowPosition(1, 1);
	glutCreateWindow("CubickRubick");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	glutMouseFunc(mouse);
	glutTimerFunc(TIMER, timer, 0);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}
