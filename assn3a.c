#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

float PI = 4*atan(1); /*This pi is used only for graphics purpose, and not misused to manipulate end results*/
int radius;
int times;
int inside = 0;
int outside = 0;
int random_points[1000][2];

void geometry()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-150,-150);
	glVertex2f(-150,150);
	glVertex2f(150,150);
	glVertex2f(150,-150);
	glEnd();

	glBegin(GL_LINE_LOOP);
	for (int k = 0;k < 1000;k++)
	{
		glVertex2f(radius*cos(PI/500*k),radius*sin(PI/500*k));
	}
	glEnd();
	glFlush();
}
void display(int argc, char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Simple Diagram");
	gluOrtho2D(-300,300,-300,300);
	glutDisplayFunc(geometry);
	glutMainLoop();
}

void input_radius()
{
	printf("%s","Give a valid radius, less than 150: ");
	scanf("%i", &radius);

	if (radius > 150)
	{
		printf("%s","Please enter a valid radius\n");
		exit(-1);
	}
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	input_radius();
	for (int i=0;i <= 999; i++)
	{
		random_points[i][0] = (rand() % 100);
		random_points[i][1] = (rand() % 100);
	};
	
	for (int j=0; j <= 999; j++)
	{
		if (sqrt((random_points[j][0]-50)^2+(random_points[j][1]-50)^2) <= radius)
		{
			++inside;
		}
		
		else
		{
			++outside;
		};
	printf("The current status of inside and outside are %i and %i\n",inside, outside);
	}
	/*We have area_in/area_out = (pi*r^2)/(a^2-pi*r^2)*/
	printf("The current status of inside and outside are %i and %i\n",inside, outside);
	float ratio = inside/outside;
	printf("The experimental ratio is %f \n",ratio);
	printf("%s","But the theoretical ratio is (pi*r^2)/(a^2-pi*r^2)\n");
	double pi = (ratio*10000)/((ratio+1)*(radius^2));
	printf("Therefore the estimated value of pi through this monte Carlo Simulation is %f \n", pi);
	printf("This Graphic object depicts the position of points in the circle and square (feel free to use Alt + F4, to close the window object)\n");
	display(argc, argv);
}