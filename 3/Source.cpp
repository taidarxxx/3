#include <cstdio>
#include <GL/glew.h>
#include <GL/freeglut.h>
#ifndef MATH_3D_H
#define	MATH_3D_H


struct Vector3f
{
	float x, y, z;

	Vector3f()
	{
	}

	Vector3f(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

#endif	/* MATH_3D_H */

GLuint VBO; //переменная для хранения указателя на буфер вершин

static void RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT); //очищаем буфер кадра

	glEnableVertexAttribArray(0); //индексируем атрибут вершины
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //обратно привязываем буфер, приготавливая его для отрисовки
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //говорим конвейеру как воспринимать данные внутри буфера

	glDrawArrays(GL_TRIANGLES, 0, 3); //вызываем функцию для отрисовки

	glDisableVertexAttribArray(0); //отключаем атрибут вершины

	glutSwapBuffers(); //меняем фоновый буфер и буфер кадра местами
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
}

static void CreateVertexBuffer()
{
	Vector3f Vertices[3];
	Vertices[0] = Vector3f(-1.0f, -1.0f, 0.0f);
	Vertices[1] = Vector3f(1.0f, -1.0f, 0.0f);
	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); //инициализируем GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // настраиваем некоторые опции GLUT

	/*Задаём параметры окна*/
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 03");

	InitializeGlutCallbacks(); //присоединяем функцию RenderSceneCB к GLUT

	/*Инициализируем GLEW и проверяем на ошибки*/
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //устанавливаем цвет, который будет использован во время очистки буфера кадра

	CreateVertexBuffer();

	glutMainLoop(); //передаём контроль GLUT'у

	return 0;
}