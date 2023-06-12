#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <GL/glut.h>

float PI = 4*atan(1); /*This pi is used only for graphics purpose, and not misused to manipulate end results*/
int radius;
int times;
int inside = 0;
int outside = 0;

void geometry()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
	glVertex2f(-50,-50);
	glVertex2f(-50,50);
	glVertex2f(50,-50);
	glVertex2f(50,50);
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

	glutInitWindowSize(200,200);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Simple Diagram");
	gluOrtho2D(-50,50,-50,50);

	glutDisplayFunc(geometry);
	glutMainLoop();
}

void input_radius()
{
	printf("%s","Give a valid radius, less than 100: ");
	scanf("%i", &radius);

	printf("%s","Enter the number of times, the simulation is to be done (Give some large numbers for better results)\n");
	scanf("%i",&times);

	if (radius > 100.001)
	{
		printf("%s","Please enter a valid radius\n");
		exit(-1);
	}
}

int main(int argc, char** argv)
{
	display(argc, argv);
	int random_points[1000][2];
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
}
