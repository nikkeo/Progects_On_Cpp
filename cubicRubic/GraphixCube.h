#ifndef _GRAPHIXCUBE_H
#define _GRAPHIXCUBE_H
 
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h> 

 
unsigned int C[9] = {0xFAEBD7, 0xFFFF00, 0x0000FF, 0x5CCD32, 0xFF0000, 	0xFFa812};

 struct Small_Cube
{
	unsigned int color[6]; 
	double size;
 
	Small_Cube() 
	{
		memset(color, 0, sizeof(color));
		size = 0.0;
	}
 
	void rotateZ()
	{
		unsigned int tmp = color[5];
		color[5] = color[3];
		color[3] = color[4];
		color[4] = color[2];
		color[2] = tmp;
	}
 
	void rotateY()
	{
		unsigned int tmp = color[2];
		color[2] = color[1];
		color[1] = color[3];
		color[3] = color[0];
		color[0] = tmp;
	}
 
	void rotateX()
	{
		unsigned int tmp = color[0];
		color[0] = color[4];
		color[4] = color[1];
		color[1] = color[5];
		color[5] = tmp;
	}
 
	void setColor(int i, unsigned int color)
	{
		this->color[i] = color;
	}

	int getColor(int i){
		if (color[i] == 0xFAEBD7){
			return 1;
		}
		if (color[i] == 0xFFFF00){
			return 2;
		}
		if (color[i] == 0x0000FF){
			return 3;
		}
		if (color[i] == 0x5CCD32){
			return 4;
		}
		if (color[i] == 0xFF0000){
			return 5;
		}
		return 6;
	}
 
	unsigned char *at(unsigned int i)
	{
		// 3 составляющих RGB
		_color[0] = color[i] >> 16;
		_color[1] = color[i] >>  8;
		_color[2] = color[i]      ;
		return _color;
	}
 
	void draw()
	{
		glPushMatrix();
		glBegin(GL_QUADS);
 
		// спереди
		glColor3ubv(at(2));
		glNormal3f(0, -1, 0);
		glVertex3f(size, 0, size);
		glVertex3f(0, 0, size);   
		glVertex3f(0, 0, 0);      
		glVertex3f(size, 0, 0); 
 
		// сзади
		glColor3ubv(at(3));
		glNormal3f(0, 1, 0);
		glVertex3f(size, size, 0);   
		glVertex3f(0, size, 0);      
		glVertex3f(0, size, size);   
		glVertex3f(size, size, size);
 
		// слева
		glColor3ubv(at(4));
		glNormal3f(-1, 0, 0);
		glVertex3f(0, size, size);   
		glVertex3f(0, size, 0);      
		glVertex3f(0, 0, 0);         
		glVertex3f(0, 0, size);      
 
		// справа
		glColor3ubv(at(5));
		glNormal3f(1, 0, 0);
		glVertex3f(size, size, 0);
		glVertex3f(size, size, size);
		glVertex3f(size, 0, size);   
		glVertex3f(size, 0, 0); 

		// верх
		glColor3ubv(at(0));
		glNormal3f(0, 0, 1);
		glVertex3f(size, size, size);          
		glVertex3f(0, size, size);          
		glVertex3f(0, 0, size);          
		glVertex3f(size, 0, size);      
 
		// низ
		glColor3ubv(at(1));
		glNormal3f(0, 0, -1);
		glVertex3f(size, 0, 0);
		glVertex3f(0, 0, 0);   
		glVertex3f(0, size, 0);  
		glVertex3f(size, size, 0);     
 
		glEnd();
		glPopMatrix();
	}
 
	// отрисовка со смещением
	void draw(double x, double y, double z)
	{
		glPushMatrix();
		glTranslated(x, y, z);
		draw();
		glPopMatrix();
	}
 
private:
	unsigned char _color[4];
};


class Cube
{
	Small_Cube a[3][3][3];
	unsigned int rotate[6], color[6];
	double size;
 
public:
	unsigned int current;
 
	Cube(){}
 
	Cube(double size, unsigned int *color) 
	{
		clear(size, color);
	}
 
	void clear(double size, unsigned int *color) 
	{
		memset(rotate, 0, sizeof(rotate));
		this->size = size;
		current = -1;
 
		unsigned int i, j, k;
		for(i = 0; i < 6; i++)
			this->color[i] = color[i];
 
		// верх
		for(i = 0; i < 3; i++)
			for(j = 0; j < 3; j++)
				a[i][j][2].setColor(0, color[0]);
 
		// низ
		for(i = 0; i < 3; i++)
			for(j = 0; j < 3; j++)
				a[i][j][0].setColor(1, color[1]);
 
		// спереди
		for(k = 0; k < 3; k++)
			for(j = 0; j < 3; j++)
				a[j][0][k].setColor(2, color[2]);
 
		// сзади
		for(k = 0; k < 3; k++)
			for(j = 0; j < 3; j++)
				a[j][2][k].setColor(3, color[3]);
 
		// слева
		for(i = 0; i < 3; i++)
			for(k = 0; k < 3; k++)
				a[0][k][i].setColor(4, color[4]);
 
		// справа
		for(i = 0; i < 3; i++)
			for(k = 0; k < 3; k++)
				a[2][k][i].setColor(5, color[5]);
 
		// устанавливаем размеры маленьких кубиков, 0.9 - прогалы между кубиков, чтобы они не были сплошняком
		for(i = 0; i < 3; i++)
			for(j = 0; j < 3; j++)
				for(k = 0; k < 3; k++)
					a[i][j][k].size = (size / 3) * 0.9;
	}

	void fillIn(double size){
		memset(rotate, 0, sizeof(rotate));
		this->size = size;
		current = -1;

		std::ifstream fin("input.txt");
		unsigned int readColor;
		unsigned int i, j, k;
 
		// верх
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++){
				fin >> readColor;
				a[i][j][2].setColor(0, C[readColor - 1]);
			}

 
		// низ
		for(int i = 0; i < 3; i++)
			for(int j = 0; j < 3; j++){
				fin >> readColor;
				a[i][j][0].setColor(1, C[readColor - 1]);
			}
 
		// спереди
		for(int k = 0; k < 3; k++)
			for(int j = 0; j < 3; j++){
				fin >> readColor;
				a[j][0][k].setColor(2, C[readColor - 1]);
			}
 
		// сзади
		for(int k = 0; k < 3; k++)
			for(int j = 0; j < 3; j++){
				fin >> readColor;
				a[j][2][k].setColor(3, C[readColor - 1]);
			}
 
		// слева
		for(int i = 0; i < 3; i++)
			for(int k = 0; k < 3; k++){
				fin >> readColor;
				a[0][k][i].setColor(4, C[readColor - 1]);
			}
 
		// справа
		for(int i = 0; i < 3; i++)
			for(int k = 0; k < 3; k++){
				fin >> readColor;
				a[2][k][i].setColor(5, C[readColor - 1]);
			}

		check(size);
	}

	void fillOut(double size){
		std::ofstream fout("output.txt");

		// верх
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				fout << a[i][j][2].getColor(0) << " ";
			}
			fout << std::endl;
		}
		fout << std::endl;

 
		// низ
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				fout << a[i][j][0].getColor(1) << " ";
			}
			fout << std::endl;
		}
 		fout << std::endl;

		// спереди
		for(int k = 0; k < 3; k++){
			for(int j = 0; j < 3; j++){
				fout << a[j][0][k].getColor(2) << " ";
			}
			fout << std::endl;
		}
 		fout << std::endl;

		// сзади
		for(int k = 0; k < 3; k++){
			for(int j = 0; j < 3; j++){
				fout << a[j][2][k].getColor(3) << " ";
			}
			fout << std::endl;
		}
		fout << std::endl;
 
		// слева
		for(int i = 0; i < 3; i++){
			for(int k = 0; k < 3; k++){
				fout << a[0][k][i].getColor(4) << " ";
			}
			fout << std::endl;
		}
		fout << std::endl;
 
		// справа
		for(int i = 0; i < 3; i++){
			for(int k = 0; k < 3; k++){
				fout << a[2][k][i].getColor(5) << " ";
			}
			fout << std::endl;
		}
	}

	bool check(double size){
		int arr[6];

		for (int i = 0; i < 6; ++i){
			arr[i] = 0;
		}

		// верх
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				arr[a[i][j][2].getColor(0) - 1] += 1;
			}
		}

 
		// низ
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				arr[a[i][j][0].getColor(1) - 1] += 1;
			}
		}

		// спереди
		for(int k = 0; k < 3; k++){
			for(int j = 0; j < 3; j++){
				arr[a[j][0][k].getColor(2) - 1] += 1;
			}
		}

		// сзади
		for(int k = 0; k < 3; k++){
			for(int j = 0; j < 3; j++){
				arr[a[j][2][k].getColor(3) - 1] += 1;
			}
		}
 
		// слева
		for(int i = 0; i < 3; i++){
			for(int k = 0; k < 3; k++){
				arr[a[0][k][i].getColor(4) - 1] += 1;
			}
		}
 
		// справа
		for(int i = 0; i < 3; i++){
			for(int k = 0; k < 3; k++){
				arr[a[2][k][i].getColor(5) - 1] += 1;
			}
		}

		for (int i = 0; i < 6; ++i){
			if (arr[i] != 9){
				std::cout << "ERROR, CUBE IS NOT VALID" << std::endl;
				exit(0);
				return 0;
			}
		}

		std::cout << "CUBE IS VALID" << std::endl;
	}

	void draw()
	{
		const double K = 0.65;

		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslatef(((1.0 - K)/2)*size + K*size/2, ((1.0 - K)/2)*size + K*size/2, ((1.0 - K)/2)*size + K*size/2);
		glutSolidCube(size * K);
		glPopMatrix();
 
		memset(peace, true, sizeof(peace));
		if (current != -1)
		{
			glPushMatrix();
			unsigned int i, j, k;
 
			if (current == 0 || current == 1)
			{
				k = (current & 1) * 2;
				for(i = 0; i < 3; i++)
					for(j = 0; j < 3; j++)
						peace[i][j][k] = false;
 
				glTranslated(size / 2, size / 2, 0);   
				glRotatef(rotate[current], 0, 0, 1);  
				glTranslated(-size / 2, -size / 2, 0); 

				for(i = 0; i < 3; i++)
					for(j = 0; j < 3; j++)
						a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
			}
			else if (current == 2 || current == 3)
			{
				j = (current & 1) * 2;
				for(i = 0; i < 3; i++)
					for(k = 0; k < 3; k++)
						peace[i][j][k] = false;
 
				glTranslated(size / 2, 0, size / 2);
				glRotatef(rotate[current], 0, 1, 0);
				glTranslated(-size / 2, 0, -size / 2);
				for(i = 0; i < 3; i++)
					for(k = 0; k < 3; k++)
						a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
			}
			else if (current == 4 || current == 5)
			{
				i = (current & 1) * 2;
				for(j = 0; j < 3; j++)
					for(k = 0; k < 3; k++)
						peace[i][j][k] = false;
 
				glTranslated(0, size / 2, size / 2);
				glRotatef(rotate[current], 1, 0, 0);
				glTranslated(0, -size / 2, -size / 2);
				for(j = 0; j < 3; j++)
					for(k = 0; k < 3; k++)
						a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
			}
			glPopMatrix();
		}
 
		for(unsigned int i = 0; i < 3; i++)
			for(unsigned int j = 0; j < 3; j++)
				for(unsigned int k = 0; k < 3; k++)
					if (peace[i][j][k])
						a[i][j][k].draw(size / 3 * i, size / 3 * j, size / 3 * k);
	}
 
public:
	std::vector <std::pair <int, bool> > solution;

	void rot90(unsigned int idx, unsigned int sign)
	{
		unsigned int i, j, k;

		if (sign == -1)
			sign = 3;
		while(sign--)
		{
			if (idx == 0 || idx == 1)
			{
				// низ/верх
				k = (idx & 1) * 2;
				for(i = 0; i < 3; i++)
					for(j = 0; j < 3; j++)
						tmp[j][2 - i] = a[i][j][k];
				for(i = 0; i < 3; i++)
					for(j = 0; j < 3; j++)
						tmp[i][j].rotateZ(), a[i][j][k] = tmp[i][j];
			}
			else if (idx == 2 || idx == 3)
			{
				// лево/право
				j = (idx & 1) * 2;
				for(i = 0; i < 3; i++)
					for(k = 0; k < 3; k++)
						tmp[k][2 - i] = a[i][j][k];
				for(i = 0; i < 3; i++)
					for(k = 0; k < 3; k++)
						tmp[i][k].rotateX(), a[i][j][k] = tmp[i][k];
			}
			else if (idx == 4 || idx == 5)
			{
				// впереди/сзади
				i = (idx & 1) * 2;
				for(j = 0; j < 3; j++)
					for(k = 0; k < 3; k++)
						tmp[k][2 - j] = a[i][j][k];
				for(j = 0; j < 3; j++)
					for(k = 0; k < 3; k++)
						tmp[j][k].rotateY(), a[i][j][k] = tmp[j][k];
			}
		}
	}
 
	void Rotate(unsigned int idx, unsigned int angle)
	{
		if (current == -1 || current == idx)
		{
			rotate[idx] += angle;
 
			if (rotate[idx] % 90 != 0)
			{
				current = idx;
			}
			else
			{
				if ((rotate[idx] < 0) ^ (current == 2 || current == 3)){
					rot90(idx, 1);
					solution.push_back(std::make_pair(idx, 1));
				}
				else{
					rot90(idx, -1);
					solution.push_back(std::make_pair(idx, 0));
				}
				rotate[idx] = 0;
				current = -1;
			}
		}
	}


private:
	unsigned int _angle[4];
	bool peace[4][4][4];
	Small_Cube tmp[4][4];
};
 
#endif;
