#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int radius;
int times;
int inside = 0;
int outside = 0;

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

int main()
{
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
	}
	/*We have area_in/area_out = (pi*r^2)/(a^2-pi*r^2)*/
	
	double ratio = inside/outside;
	printf("The experimental ratio is %f \n",ratio);
	printf("%s","But the theoretical ratio is (pi*r^2)/(a^2-pi*r^2)\n");
	double pi = (ratio*10000)/((ratio+1)*(1 << radius));
	printf("Therefore the estimated value of pi through this monte Carlo Simulation is %f \n", pi);
}
