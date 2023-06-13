#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

float PI = 4*atan(1); /*This pi is used only for graphics purpose, and not misused to manipulate end results*/
int radius;
int inside = 0;
int outside = 0;
int random_points[1000][2];

void geometry()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-250,-250);
	glVertex2f(-250,250);
	glVertex2f(250,250);
	glVertex2f(250,-250);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int k = 0;k <= 999;k++)
	{
		glVertex2f(radius*cos(PI/500*k),radius*sin(PI/500*k));
	}
	glEnd();

	glPointSize(2);
	glBegin(GL_POINTS);
	for (int k = 0;k <= 999;k++)
	{
		glVertex2f(random_points[k][0],random_points[k][1]);
	}
	glEnd();
	glFlush();
}
void display(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Simple Diagram");
	gluOrtho2D(-500,500,-500,500);
	glutDisplayFunc(geometry);
	glutMainLoop();
}

void input_radius()
{
	printf("%s","Give a valid radius, less than 250: ");
	scanf("%i", &radius);

	if (radius > 250 || radius < 0)
	{
		printf("%s","Please enter a valid radius\n");
		exit(-1);
	}
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	input_radius();
	for (int i = 0;i <= 999; i++)
	{
		random_points[i][0] = (rand() % 500)-250;
		random_points[i][1] = (rand() % 500)-250;

		if (sqrt((random_points[i][0])^2+(random_points[i][1])^2) <= radius)
		{
			++inside;
		}
		
		else
		{
			++outside;
		};
	};
	
	printf("The current status of inside and outside are %i and %i\n",inside, outside);
	
	/*We have area_in/area_out = (pi*r^2)/(a^2-pi*r^2). assuming uniform and random distribution of points, this ratio should be equal to ratio of inside and outside points*/
	float ratio = (inside/outside)*1.000000;
	printf("The experimental ratio is %.6f \n",ratio);
	printf("%s","But the theoretical ratio is (pi*r^2)/(a^2-pi*r^2)\n");
	
	double pi = (inside*250.000000)/(radius*radius); /*because sum of no. of points inside and outside the circle equals 1000*/
	printf("Therefore the estimated value of pi through this Monte Carlo Simulation is %.6f \n", pi);
	printf("This Graphic object depicts the position of points in the circle and square (feel free to use Alt + F4, to close the window object)\n");
	display(argc, argv);
}